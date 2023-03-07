# vk_badapple_cpp
Badapple bot for VKontakte

![](git_res/Youmu.gif)

## Dependencies
- OpenCV
For prepare_video.sh:
- yt-dlp // youtube-dl

## Building
```sh
git submodule init
git submodule update
cmake .
cmake --build ./ -j$(nproc)
# Now binary is in ./build
```

## Prepairing to start
```sh
# Get badapple video => ./build/badapple.webm
# yt-dlp // youtube-dl require
./prepare-video.sh

# Get a config sample file
cp ./modules/cpp_vk_lib/json_schema/sample_config.json ./build/config.json
# Enter token in config (group token tested only) and path to logs.txt
```

## Finally
```sh
cd build
./vk_baddapple_cpp <config.json>
```

## Known issues
- VK limits the number of message edits
Workaround: After an error occurs, send frames with a new message

Based on [cpp_vk_lib](https://gitlab.com/epoll-reactor/cpp_vk_lib)
