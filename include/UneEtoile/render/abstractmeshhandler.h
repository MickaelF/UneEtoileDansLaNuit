#pragma once

class Mesh;
class IRenderIDCard;

class AbstractMeshHandler
{
public:
    AbstractMeshHandler() = default;
    virtual ~AbstractMeshHandler();

    virtual IRenderIDCard* load(Mesh& mesh) = 0;
    virtual void unload(IRenderIDCard* card) = 0;

private: 

};