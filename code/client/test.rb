#!env ruby

require 'uri'
require 'net/http'

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

# start loop over columns
num_modules.times do |m|
  num_columns[m].times do |c|
    num_rows.times do |r|
      int_output[r][m] = 0
    end

    # set all rows at this column
    num_rows.times do |r|
      int_output[r][m] = 1<<c
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

    # print POST query
    puts "dots_query_string(#{dots_query_string.length}) = #{dots_query_string.inspect}"

    # clear
    if DO_HTTP
      res = Net::HTTP.start(flippie_ip) do |http|
        http.get('/flipdot?task=clear')
      end
      puts res.body
    end

    # HTTP connect to flippie and POST dots query
    if DO_HTTP
       uri = URI("http://#{flippie_ip}/dots")
       http = Net::HTTP.new(uri.host, uri.port, nil, nil)
       request = Net::HTTP::Post.new(uri.path)
       request.set_form_data({'dots' => dots_query_string})
       puts http.request(request)
    end
  end
end
