#pragma once

class BasicShader
{
public:
    explicit BasicShader();

    unsigned int programId() const { return m_programId; }

private:
    unsigned int m_programId;
}