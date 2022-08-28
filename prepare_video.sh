#!/bin/sh

if [ $(which yt-dlp) ];then
	yt-dlp -o badapple "https://www.youtube.com/watch?v=UkgK8eUdpAo"
else
	youtube-dl -o badapple.webm -x -f 278 "https://www.youtube.com/watch?v=UkgK8eUdpAo"
fi

mkdir -p ./build
mv ./badapple.webm ./build/badapple.webm
