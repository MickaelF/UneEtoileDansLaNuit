#pragma once
#include <filesystem>
#include <map>
#include <memory>

class Texture;

class TextureFactory
{
public:
    static TextureFactory& instance();
    Texture* generateTexture(const std::filesystem::path& path);
    void unloadTexture(Texture* tex);

private:
    explicit TextureFactory() = default;
    TextureFactory(const TextureFactory&) = delete;
    TextureFactory(TextureFactory&&) = delete;
    TextureFactory& operator=(const TextureFactory&) = delete;
    TextureFactory& operator=(TextureFactory&&) = delete;
    std::map<std::filesystem::path, std::unique_ptr<Texture>> m_generatedTexture;
};