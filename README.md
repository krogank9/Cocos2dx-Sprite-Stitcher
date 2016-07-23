# Cocos2dx-Sprite-Stitcher

Depends:
Imagemagick, bash, etc1tool from android sdk

Usage:
1. Download the command line tools: png2etc1, png2etc1_a, png2stitch, png2stitch_a.
-png2etc1 converts PNG files to ETC1 format compressed (PKM) files
-png2stitch will convert a large png (greater than 1024x1024px) to a set of tiles, to be passed into SpriteStitcher Cocos2dx class.
-png2etc1_a converts PNG files to ETC1 format but with their alpha channel encoded into a seperate file.
-png2stitch_a will convert a large png into tiles, but each tile has its own alpha map

2. Command line tool usage:
png2etc1 file1.png file2.png file3.png ... // outputs a .pkm for every in file
png2etc1_a file1.png file2.png file3.png ... // outputs a .pkm & _alpha.pkm for every in file
png2stitch

3. Download Cocos2d-x project files:
-shaders/ folder, place this in your Cocos2d-x project's Resources/ directory
-SpriteStitch.cpp use this class inside your Cocos2d-x project to obtain a SpriteStitch node

4. SpriteStitch class usage:
Initialize a SpriteStitch object from the output of png2stitch:
node = SpriteStitch::createFromFolder("level1", true);

Just create a ETC1 compressed sprite with alpha:
sprite = SpriteStitch::createETCASprite("Sprite.pkm", "Sprite_alpha.pkm");
First arguement is the sprite's pkm image file, the second is the sprite's alpha mask (created with png2etc_a)
