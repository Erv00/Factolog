# Factolog language spec
    async module Foo(in sig1, in sig2, out osig){
        var s;
        Bar(sig1, s);
        osig = s & sig2;
    }

    sync module Bar(clk clk, in isig, out osig){
        reg curr_state {STATE0, STATE1, STATE2};
        
        switch(curr_state){
            STATE0:
                if(isig == 0){
                    curr_state = STATE1;
                }else{
                    curr_state = STATE2;
                }
            STATE1:
                #Snip
            STATE2:
                #Snip
        }

        osig = curr_state;
    }
