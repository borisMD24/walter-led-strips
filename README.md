# walter-led-strips

## ino code for the walter led-strip code !

### currently working on the offline portal


### to do :

    the "gradient" function 
    how :
        * compute the steps with length
        * compute each step
        * apply via array of instance
    
    gradient interpretor
    how : 
        [
            {
                offset : {
                    nbr (%), //a convertir avec la length
                    color : [
                        r,
                        g,
                        b
                    ]
                }
            }
        ]
    sortir un array de led


IMPORTANT

faire un classe led < adafruit neopixel
    faire une classe strip < adafruit neopixel
        faire une classe de section
            faire une class WalterLedStrip < adafruit neopixel
