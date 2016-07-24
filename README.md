# Cocos2dx-Sprite-Stitcher

https://www.youtube.com/watch?v=kc1TuY8kIj0

##Dependencies:
Imagemagick, bash, etc1tool from android sdk

##Command line tools:
1. `png2etc1` converts PNG files to ETC1 format compressed (PKM) files
2. `png2stitch` will convert a large png (greater than 1024x1024px) to a set of tiles, to be passed into SpriteStitcher Cocos2dx class.
3. `png2etc1_a` converts PNG files to ETC1 format but with their alpha channel encoded into a seperate file.
4. `png2stitch_a` will convert a large png into tiles, but each tile has its own alpha map

##Command line tool usage:
1. `png2etc1 file1.png file2.png file3.png ...` outputs a .pkm for every infile
2. `png2etc1_a file1.png file2.png file3.png ...` outputs a .pkm & _alpha.pkm for every infile
3. `png2stitch image_name.png` outputs folder image_name, containing a number of .pkm tiles <= 1024x1024 depending on image size
3. `png2stitch_a image_name.png` same as png_stitch but each tile also comes with an alpha map

##Download Cocos2d-x project files:
1. `shaders/` folder, place this in your Cocos2d-x project's `Resources/` directory
2. `SpriteStitch.cpp` and `SpriteStitch.h` use this class inside your Cocos2d-x project to obtain a SpriteStitch node
3. To add a class this class into your Windows or Linux build, edit CMakeLists.txt at the root of your project directory to add the files, then run `cmake -G "Unix Makefiles"` (or appropriate generator-name) in your `proj.linux/` or `proj.win32/` folder

##SpriteStitch class usage:
1. Initialize a SpriteStitch object from the output of png2stitch:
   `node = SpriteStitch::createFromFolder("level1", true);`
   First argument is the folder outputted from png2stitch, second argument is if it has an alpha mask, true/false

2. Create ETC1 compressed sprite with alpha:
   `sprite = SpriteStitch::createETCASprite("Sprite.pkm", "Sprite_alpha.pkm");`
   First argument is the sprite's pkm image file, the second is the sprite's alpha mask (created with png2etc_a)
