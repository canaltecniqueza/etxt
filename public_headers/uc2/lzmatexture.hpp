/**
 * @file lzmatexture.hpp
 * @author Luís Leite (luis@leite.xyz)
 * @brief Decompresses LZMA'd VTFs
 * @version 1.0
 *
 * Contains a class that decompresses Valve Texture Files that were compressed
 * with LZMA.
 */

#pragma once

#include "uc2defs.h"

#include <cstdint>
#include <memory>
#include <vector>

/**
 * @brief The libuncso2's namespace.
 */
namespace uc2
{
/**
 * @brief Decompresses LZMA'd VTFs.
 *
 * Decompresses Valve Texture Files that were compressed
 * with LZMA.
 */
class UNCSO2_API LzmaTexture
{
public:
    using ptr_t = std::unique_ptr<LzmaTexture>; /*!< The pointer type of
                                                     LzmaTexture. */

    virtual ~LzmaTexture() = default;

    /**
     * @brief Retrieves the texture's real size.
     *
     * Retrieves the real texture's size from its compressed LZMA header.
     *
     * @return std::uint64_t the texture's real size.
     */
    virtual std::uint64_t GetOriginalSize() = 0;

    /**
     * @brief Decompresses the texture.
     *
     * Decompresses the texture using LZMA.
     * The user must allocate and provide the outBuffer.
     * The buffer must have the size returned in the method GetOriginalSize.
     * The outBufferSize must be the same as the result of the method
     * GetOriginalSize.
     *
     * @param outBuffer The user's allocated out buffer.
     * @param outBufferSize The out buffer's size.
     * @return true if it was decompressed successfully.
     * @return false if it failed to decompress.
     */
    virtual bool Decompress(std::uint8_t* outBuffer,
                            std::uint64_t outBufferSize) = 0;

    /**
     * @brief Does the buffer data's have an LZMA texture header?
     *
     * Validates the data's size and checks the header's magic signature.
     *
     * @param pData The buffer data.
     * @param iDataSize THe buffer's size.
     * @return true If the buffer data has an LZMA texture header.
     * @return false If the buffer data does NOT have an LZMA texture header.
     */
    static bool IsLzmaTexture(std::uint8_t* pData,
                              const std::uint64_t iDataSize);

    /**
     * @brief Gets the size of a compressed texture's header.
     *
     * @return std::uint64_t The size of a compressed texture's header.
     */
    static std::uint64_t GetHeaderSize();

    /**
     * @brief Construct a new CompressedTexture object.
     *
     * The texture's data input passed in texData is not modified.
     *
     * This method throws exceptions:
     * - It throws std::invalid_argument when the texture's header is invalid.
     *
     * @param texData A reference to the compressed texture's data.
     * @return ptr_t the new CompressedTexture object.
     */
    static ptr_t Create(std::vector<std::uint8_t>& texData);

    /**
     * @brief Construct a new CompressedTexture object.
     *
     * The texture's data input passed in texData is not modified.
     *
     * This method throws exceptions:
     * - It throws std::invalid_argument when the texture's header is invalid.
     *
     * @param pData The texture's data buffer.
     * @param iDataSize The texture's data buffer size.
     * @return ptr_t the new CompressedTexture object.
     */
    static ptr_t Create(std::uint8_t* pData, const std::uint64_t iDataSize);
};
}  // namespace uc2
