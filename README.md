# Cocos2dx-Sprite-Stitcher

Depends:
Imagemagick, bash, etc1tool from android sdk

#Command line tools
1. png2etc1 converts PNG files to ETC1 format compressed (PKM) files
2. png2stitch will convert a large png (greater than 1024x1024px) to a set of tiles, to be passed into SpriteStitcher Cocos2dx class.
3. png2etc1_a converts PNG files to ETC1 format but with their alpha channel encoded into a seperate file.
4. png2stitch_a will convert a large png into tiles, but each tile has its own alpha map

#Command line tool usage:
1. `png2etc1 file1.png file2.png file3.png ... // outputs a .pkm for every in file`
2. `png2etc1_a file1.png file2.png file3.png ... // outputs a .pkm & _alpha.pkm for every in file`
3. `png2stitch image_name.png // outputs folder image_name, containing a number of .pkm tiles <= 1024x1024 depending on image size`
3. `png2stitch_a image_name.png // same as png_stitch but each tile also comes with an alpha map`

#Download Cocos2d-x project files:
1. shaders/ folder, place this in your Cocos2d-x project's Resources/ directory
2. SpriteStitch.cpp use this class inside your Cocos2d-x project to obtain a SpriteStitch node

#SpriteStitch class usage:
1. Initialize a SpriteStitch object from the output of png2stitch:
   `node = SpriteStitch::createFromFolder("level1", true);`
   First arguement is the folder outputted from png2stitch, second argument is if it has an alpha mask, true/false

2. Just create a ETC1 compressed sprite with alpha:
   `sprite = SpriteStitch::createETCASprite("Sprite.pkm", "Sprite_alpha.pkm");`
   First arguement is the sprite's pkm image file, the second is the sprite's alpha mask (created with png2etc_a)
