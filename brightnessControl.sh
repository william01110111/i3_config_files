current=$(cat /sys/class/backlight/intel_backlight/actual_brightness)

max=$(cat /sys/class/backlight/intel_backlight/max_brightness)

actualChange=$(($1*$max/100))

new=$(($current+$actualChange))

if (( $new > $max )); then
    new=$max
fi

if (( $new < $max/16 )); then
    new=$(($max/16))
fi

sudo tee /sys/class/backlight/intel_backlight/brightness <<< $new

