#pragma once

#include <UneEtoile/render/abstractmeshhandler.h>

class CommonGLMeshHandler : public AbstractMeshHandler
{
public:
    CommonGLMeshHandler() = default;
    virtual ~CommonGLMeshHandler();

    IRenderIDCard* load(Mesh& mesh) override;
    void unload(IRenderIDCard* card) override;
};