#!/bin/bash


function PngFileName() {
    local input_file_name="$1"
    echo "${input_file_name}" | sed -e 's/[^\.]*$/png/'
}

function FinalGraphFileName() {
    local input_file_name="$1"

    local prefix="$( basename "${input_file_name}" | sed -e 's/^\([0-9FR]\+\)-.*/\1/' )"
    local folder="$( dirname "${input_file_name}" )"

    echo "${folder}/${prefix}-graph.png"
}

function HighPassWav() {
    local input_wav="$1"
    local final_graph_png="$( FinalGraphFileName "${input_wav}" )"

    # Защита от того, чтобы не заездить wav-файл high-passами до смерти.
    # Делаем High-Pass проход только в том случае, если wav-файл свежее,
    # чем его график. Если старше, значит, уже делали.
    [ "${input_wav}" -ot "${final_graph_png}" ] && return

    local temp_wav="$( /bin/mktemp --tmpdir='/tmp' 'hamster_sound_XXXXXXXXXX.wav' )"

    ffmpeg -y -i "${input_wav}" -filter:a 'highpass=f=100' "${temp_wav}"
    mv -f "${temp_wav}" "${input_wav}"
}

function DrawWaveForm() {
    local input_wav="$1"
    local output_png="$( PngFileName "${input_wav}" )"

    ffmpeg -y -i "${input_wav}" -filter_complex 'showwavespic=s=1850x200:colors=0x0000FF' -frames:v 1 "${output_png}"
}

function DrawMotorGraph() {
    local input_log="$1"
    local output_png="$( PngFileName "${input_log}" )"
    local plot_file="$( /bin/mktemp --tmpdir='/tmp' 'hamster_motor_XXXXXXXXXX.plot' )"

cat << EOF > "${plot_file}"
set terminal png truecolor size 1850, 200
set output "${output_png}"
set boxwidth 0.5
set style fill solid
set grid
set xrange [ -3 : 251 ]
set lmargin at screen 0
set rmargin at screen 1
set tmargin at screen 1
set bmargin at screen 0
set xtics offset 0, screen 0.15
set ytics offset screen 0.04, 0

plot "${input_log}" using 1 with linespoints title "Motor voltage", \
     "${input_log}" using 2 with boxes title "Trigger state"
EOF

    /usr/bin/gnuplot "${plot_file}"
    rm -f "${plot_file}"
}

function MergeGraphs() {
    local input_log="$1"
    local motor_png="$( PngFileName "${input_log}" )"
    local sound_png="${motor_png/motor/sound}"
    local output_graph_png="$( FinalGraphFileName "${input_log}" )"

    composite -blend 50 "${sound_png}" "${motor_png}" "${output_graph_png}"
    rm -f "${sound_png}" "${motor_png}"
}

function ClickCodePNGCard() {
    local input_log="$1"
    local prefix="$( basename "${input_log}" | sed -e 's/^\([0-9]\+\)[FR]-.*/\1/' )"
    local folder="$( dirname "${input_log}" )"
    local dec_code="${prefix//0/}"

    local convert_args=('-size' '130x50' 'xc:none' '-fill' 'black')

    for (( i = 0; i < 6; ++i ))
    do
        local right_bit=$(( dec_code & (1 << i) ))
        convert_args=("${convert_args[@]}" '-draw' "rectangle $(( i * 20 + 10)),10 $(( i * 20 + 20)),20")
        [ "${right_bit}" != '0' ] && convert_args=("${convert_args[@]}" '-draw' "rectangle $(( i * 20 + 10)),30 $(( i * 20 + 20)),40")
    done

    convert_args=("${convert_args[@]}" "${folder}/${prefix}-click-code.png")
    convert "${convert_args[@]}"
}


for wav_file in 'report/'*.wav
do
    HighPassWav "${wav_file}"
    DrawWaveForm "${wav_file}"
done

for log_file in 'report/'*.log
do
    DrawMotorGraph "${log_file}"
    MergeGraphs "${log_file}"
    ClickCodePNGCard "${log_file}"
done

#convert -size 120x60 xc:white -fill black -draw "rectangle 25,10 95,50" -draw "rectangle 30,15 90,45" rect.png
