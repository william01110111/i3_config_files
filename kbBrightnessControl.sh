
current=$(cat /sys/class/leds/smc::kbd_backlight/brightness)

max=$(cat /sys/class/leds/smc::kbd_backlight/max_brightness)
min=0

actualChange=$(($1*$max/100))

new=$(($current+$actualChange))

if (( $new > $max )); then
    new=$max
fi

if (( $new < $min )); then
    new=$min
fi

echo brightness set to $new "("range is $min - $max")"

sudo tee /sys/class/leds/smc::kbd_backlight/brightness <<< $new
#/home/william/.config/i3/WidapPopup/WidapPopupRun kb-brightness $(($new*100/$max))

