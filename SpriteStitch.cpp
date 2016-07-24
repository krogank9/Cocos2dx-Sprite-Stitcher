#include "cocos2d.h"
#include "SpriteStitch.h"

USING_NS_CC;
using namespace std;

SpriteStitch::SpriteStitch(const string& stitchFolder, bool hasAlpha)
{
    // parent of all the sprites we're about to create
    Node* parentNode = Node::create();
    this->addChild(parentNode);

    int xPos = 0;
    int yPos = 0;
    int rowWidth, rowHeight;
    int x,y;
    bool loop = true;
    // Loop through all the tile sprites in stichFolder and add them as children
    for(y=0; loop; y++)
    {
        for(x=0, xPos=0; ; x++)
        {
            stringstream file, alphaFile;
            file << stitchFolder << "/" << x << "-" << y << ".pkm";
            alphaFile << stitchFolder << "/" << x << "-" << y << "_alpha.pkm";

            Sprite* sprite;
            if(hasAlpha) sprite = createETCASprite( file.str().c_str(), alphaFile.str().c_str() );
            else sprite = Sprite::create(file.str().c_str());

            if(sprite == nullptr)
            {
                if(x==0) // If we hit an empty row, there are no more sprites to load
                {
                    loop = false;
                }
                else // Row wasn't empty, but it's the end of row
                {
                    yPos -= rowHeight;
                    rowWidth = xPos;
                }

                break;
            }
            rowHeight = sprite->getContentSize().height;
            parentNode->addChild(sprite);
            sprite->setAnchorPoint(Vec2(0,1));
            sprite->setPosition(xPos, yPos);

            //incr x position for next sprite tile
            xPos += sprite->getContentSize().width;
        }
    }
    // Imagemagick outputs tiles with (0,0) at the top left, but in cocos (0,0) is the bottom left.
    // Flip the children back around the x axis
    parentNode->setPosition(0,-yPos);

    Size stitchSize(rowWidth, -yPos);
    this->setContentSize(stitchSize);
}

SpriteStitch* SpriteStitch::createFromFolder(const string& stitchFolder, bool hasAlpha)
{
    SpriteStitch* pRet = new SpriteStitch(stitchFolder, hasAlpha);
    pRet->autorelease();
    return pRet;
}

// Helper function to create a transparent sprite using ETC format with an alpha mask
Sprite* SpriteStitch::createETCASprite(const string& file, const string& alphaFile)
{
    Sprite* sprite = Sprite::create(file);
    if( sprite == nullptr ) return nullptr; // abort

    Texture2D* tex = Director::getInstance()->getTextureCache()->addImage(alphaFile);
    if(tex == nullptr) return sprite; // no alpha file available

    sprite->setBlendFunc((BlendFunc) { GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA });

    GLProgram* glp = new GLProgram();
    glp->autorelease();
    glp->initWithFilenames("shaders/alpha.vsh", "shaders/alpha.fsh");
    glp->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_POSITION, GLProgram::VERTEX_ATTRIB_POSITION);
    glp->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_COLOR, GLProgram::VERTEX_ATTRIB_COLOR);
    glp->bindAttribLocation(GLProgram::ATTRIBUTE_NAME_TEX_COORD, GLProgram::VERTEX_ATTRIB_TEX_COORD);
    glp->link();
    glp->updateUniforms();
    GLProgramState* glprogramstate = GLProgramState::getOrCreateWithGLProgram(glp);

    sprite->setGLProgramState(glprogramstate);

    glprogramstate->setUniformTexture("u_texture1", tex);
    sprite->setGLProgram(glp);
    return sprite;
}
