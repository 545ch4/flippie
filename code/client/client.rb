#!env ruby

require 'uri'
require 'net/http'
require 'tco'
# https://github.com/viz/ruby-multipart-post/raw/master/ruby-multipart-post-0.4.0.gem
#require 'ruby-multipart-post'

# fonts
require './fonts.rb'
font = ASCII_TO_BITMAP_10X16
font_width = 10
font_height = 16
font_line_space = 0

num_rows = 18
num_modules = 4
num_columns = [28, 28, 28, 21]
flippie_ip = '192.168.1.172'
DO_HTTP = true

# init output array (main container of all data)
int_output = []
num_rows.times do
   int_output << num_modules.times.map{0}
end

# custom message
text = ARGV[0] || 'Hello world!'

# start loop over characters in "text"
current_row = 0
current_module = 0
current_column = 0

if font_width > 8
   text.each_byte do |b|
      if num_columns[current_module..-1].inject(0){|t,x| t + x} - current_column < font_width
         puts "text hard wrappped ..."
         current_row += font_height + 1
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
            if row_current_column >= num_columns[row_current_module]
               row_current_column = 0
               row_current_module += 1
            end
         end
         8.times do |w|
            if (c[h] & (1<<(7 - w))) == (1<<(7 - w))
               int_output[char_current_row][row_current_module] |= 1<<row_current_column
            end
            row_current_column += 1
            if row_current_column >= num_columns[row_current_module]
               row_current_column = 0
               row_current_module += 1
            end
         end
         char_current_row += 1
      end
      current_column += font_width + 1
      if current_column >= num_columns[current_module]
         current_column = current_column - num_columns[current_module]
         current_module += 1
      end
   end
else
   text.each_byte do |b|
      if num_columns[current_module..-1].inject(0){|t,x| t + x} - current_column < font_width
         if (current_row + font_height > num_rows) || ((current_row + font_height + font_height) > num_rows)
            puts "no space left for wrappping..."
            break
         else
            puts "text hard wrappped..."
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
            if row_current_column >= num_columns[row_current_module]
               row_current_column = 0
               row_current_module += 1
            end
         end
         char_current_row += 1
      end
      current_column += font_width + 1
      if current_column >= num_columns[current_module]
         current_column = current_column - num_columns[current_module]
         current_module += 1
      end
   end
end

# # print int array (DEBUGGING)
puts num_rows.times.map{|r| num_modules.times.map{ |m| "%010u"%(int_output[r][m])}.join(' | ')}.join("\n")

# build byte array for submission
dots_query_string = ''
current_byte = 0
current_byte_s = ''
print 'dots(int)=['
num_rows.times do |r|
   num_modules.times do |m|
      [0, 8, 16, 24].each do |shift|
        current_byte = (int_output[r][m]>>shift) & 255
        print '%u '%(current_byte)
        current_byte_s = current_byte.to_s(16)
        dots_query_string << '0' if current_byte_s.size == 1
        dots_query_string << current_byte_s
      end
      print '| '
   end
end
puts ']'

puts "dots_query_string(#{dots_query_string.length}) = #{dots_query_string.inspect}"

# HTTP connect to flippie and POST dots query
if DO_HTTP
   uri = URI("http://#{flippie_ip}/dots")
   http = Net::HTTP.new(uri.host, uri.port, nil, nil)
   request = Net::HTTP::Post.new(uri.path)
   request.set_form_data({'dots' => dots_query_string})
   puts http.request(request)

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
num_rows.times do |r|
   num_modules.times do |m|
      num_columns[m].times do |c|
         (int_output[r][m] & 1<<c) == 1<<c ? print('  '.bg('#fdea22')) : print('  ')
      end
   end
   puts
end
