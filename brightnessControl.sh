current=$(cat /sys/class/backlight/intel_backlight/actual_brightness)

max=$(cat /sys/class/backlight/intel_backlight/max_brightness)
min=0

actualChange=$(($1*$max/100))

new=$(($current+$actualChange))

if (( $new > $max )); then
    new=$max
fi

if (( $new < $min )); then
    new=$min
fi

sudo tee /sys/class/backlight/intel_backlight/brightness <<< $new

