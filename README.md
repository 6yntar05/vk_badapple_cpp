# vk_badapple_cpp
Badapple bot for VKontakte

![](https://github.com/6yntar05/vk_badapple_cxx/blob/master/git_res/Youmu.gif)

## Dependencies
- OpenCV
For prepare_video.sh:
- yt-dlp // youtube-dl

## Building
```sh
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

Based on [cpp_vk_lib](https://github.com/epoll-reactor/cpp_vk_lib)
