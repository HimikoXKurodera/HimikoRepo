def rot13(secret_messages)
  # your code here
  #retStrArr=[]
  #concatStr=""
 
  return secret_messages.collect{ |e| 
       concatStr=""
        for i in 0..e.length-1
            #(e[i]+13)%26
            #concatStr+=(((e[i]-97)+13)%26)
            if e[i].ord>=97 && e[i].ord <= 122
                #((char) ('A' + ((text.charAt(i) - 'A' + 13) % 26)))
                #concatStr+=(97+(((e[i]-97)+13)%26))
                concatStr+=(97+(((e[i].ord-97)+13)%26)).chr
            elsif e[i].ord >= 65 && e[i].ord<=90
                concatStr+=(65+(((e[i].ord-65)+13)%26)).chr
            else
                concatStr+=e[i].ord.chr
            end
            
        end
      concatStr
      
  }
  
end

