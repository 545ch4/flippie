require 'uri'
require 'net/http'
require 'tco'
require 'base64'

# fonts
require "#{File.dirname(__FILE__)}/fonts.rb"


class FlippieClient
   @debug = false

   def initialize(ip = '192.168.1.10', rows = 18, columns = [28], debug = false)
      @rows = rows.to_i
      @columns = columns
      throw ArgumentException('"columns" supposed to be an array.') unless @columns.kind_of?(Array)
      @ip = ip
      @debug = debug == true
   end

   def clear()
      res = Net::HTTP.start(flippie_ip) do |http|
        http.get('/flipdot?task=clear')
      end
      puts res.body if @debug
      true
   end

   def inspect
      "FlippieClient[#{@rows}; #{@columns.join(', ')}]@#{@ip}"
   end

   def transmit(message = 'Hello world!', font_name = '4x6', font_line_space = 1, fire = true)
      # set font specs
      font = case font_name.to_s.downcase
      when '6x8'
         ASCII_TO_BITMAP_6X8
      when '10x16'
         ASCII_TO_BITMAP_10X16
      when '12x16'
         ASCII_TO_BITMAP_12X16
      else
         font_name = '4x6'
         ASCII_TO_BITMAP_4X6
      end
      (font_width, font_height) = font_name.to_s.split(/x/i).map{|i| i.to_i}
      font_line_space = 1 if font_line_space.to_i < 0

      puts "Font => #{font_name}(#{font_width}, #{font_height}, #{font_line_space}) => #{font.size} characters" if @debug

      # init output array (main container of all data)
      int_output = []
      @rows.times do
         int_output << @columns.size.times.map{0}
      end

      # start loop over characters in "text"
      current_row = 0
      current_module = 0
      current_column = 0

      if font_width > 8
         message.each_byte do |b|
            if @columns[current_module..-1].inject(0){|t,x| t + x} - current_column < font_width
               puts "text hard wrappped ..." if @debug
               current_row += font_height + font_line_space
               current_module = 0
               current_column = 0
            end
            c = font[b]
            char_current_row = current_row
            font_height.times do |h|
               h = h * 2
               row_current_column = current_column
               row_current_module = current_module
               (font_width - 8).times do |w|
                  if (c[h + 1] & (1<<(font_width - 8 - 1 - w))) == (1<<(font_width - 8 - 1 - w))
                     int_output[char_current_row][row_current_module] |= 1<<row_current_column
                  end
                  row_current_column += 1
                  if row_current_column >= @columns[row_current_module]
                     row_current_column = 0
                     row_current_module += 1
                  end
               end
               8.times do |w|
                  if (c[h] & (1<<(7 - w))) == (1<<(7 - w))
                     int_output[char_current_row][row_current_module] |= 1<<row_current_column
                  end
                  row_current_column += 1
                  if row_current_column >= @columns[row_current_module]
                     row_current_column = 0
                     row_current_module += 1
                  end
               end
               char_current_row += 1
            end
            current_column += font_width + 1
            if current_column >= @columns[current_module]
               current_column = current_column - @columns[current_module]
               current_module += 1
            end
         end
      else
         message.each_byte do |b|
            if @columns[current_module..-1].inject(0){|t,x| t + x} - current_column < font_width
               if (current_row + font_height > @rows) || ((current_row + font_height + font_height) > @rows)
                  puts "no space left for wrappping..."  if @debug
                  break
               else
                  puts "text hard wrappped..."  if @debug
                  current_row += font_height + font_line_space
                  current_module = 0
                  current_column = 0
               end
            end
            c = font[b]
            char_current_row = current_row
            font_height.times do |h|
               row_current_column = current_column
               row_current_module = current_module
               font_width.times do |w|
                  if (c[h] & (1<<(font_width - w - 1))) == (1<<(font_width - w - 1))
                     int_output[char_current_row][row_current_module] |= 1<<row_current_column
                  end
                  row_current_column += 1
                  if row_current_column >= @columns[row_current_module]
                     row_current_column = 0
                     row_current_module += 1
                  end
               end
               char_current_row += 1
            end
            current_column += font_width + 1
            if current_column >= @columns[current_module]
               current_column = current_column - @columns[current_module]
               current_module += 1
            end
         end
      end

      # print int array (debug)
      puts @rows.times.map{|r| @columns.size.times.map{ |m| "%010u"%(int_output[r][m])}.join(' | ')}.join("\n") if @debug

      # build byte array for submission
      dots_query_string = StringIO.new
      @rows.times do |r|
         @columns.size.times do |m|
            [0, 8, 16, 24].each do |shift|
              dots_query_string.putc((int_output[r][m]>>shift) & 255)
            end
         end
      end

      puts "dots_query_string(#{dots_query_string.string.length}) = #{dots_query_string.string.inspect} = #{Base64.encode64(dots_query_string.string)}" if @debug


      # HTTP connect to flippie and POST dots query
      if fire
         uri = URI("http://#{@ip}/dots")
         http = Net::HTTP.new(uri.host, uri.port, nil, nil)
         request = Net::HTTP::Post.new(uri.path)
         request.set_form_data({'dots' => Base64.encode64(dots_query_string.string)})
         puts http.request(request) if @debug

      #   uri = URI("http://#{flippie_ip}/dots")
      #   request = Net::HTTP::Post::Multipart.new(uri.path, {'dots' => dots_query_string})
      #   response = Net::HTTP.start(uri.host, uri.port) do |http|
      #      http.request(request)
      #   end
      #   puts response

      #   multipart_post = MultiPart::Post.new({'dots' => dots_query_string})
      #   multipart_post.submit("http://#{flippie_ip}/dots")
      end

      # visualize sent output
      @rows.times do |r|
         @columns.size.times do |m|
            @columns[m].times do |c|
               (int_output[r][m] & 1<<c) == 1<<c ? print(' @'.fg('#fdea22')) : print('  ')
            end
         end
         puts
      end
      true
   end
end
