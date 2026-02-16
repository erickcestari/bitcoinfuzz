// Copyright (c) 2023 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef CUSTOMMUTATOR_CRYPTO_CHACHA20POLY1305_H
#define CUSTOMMUTATOR_CRYPTO_CHACHA20POLY1305_H

#include <cstddef>
#include <span>
#include <stdint.h>

#include <custommutator/utils/crypto/chacha20.h>
#include <custommutator/utils/crypto/poly1305.h>

/**
 * The AEAD_CHACHA20_POLY1305 authenticated encryption algorithm from RFC8439
 * section 2.8.
 */
class AEADChaCha20Poly1305 {
  /** Internal stream cipher. */
  ChaCha20 m_chacha20;

public:
  /** Expected size of key argument in constructor. */
  static constexpr unsigned KEYLEN = 32;

  /** Expansion when encrypting (16-byte Poly1305 tag). */
  static constexpr unsigned EXPANSION = Poly1305::TAGLEN;

  /** Initialize an AEAD instance with a specified 32-byte key. */
  AEADChaCha20Poly1305(std::span<const std::byte> key) noexcept;

  /** Switch to another 32-byte key. */
  void SetKey(std::span<const std::byte> key) noexcept;

  /** 96-bit nonce type. */
  using Nonce96 = ChaCha20::Nonce96;

  /**
   * Encrypt a message with a specified 96-bit nonce and aad.
   *
   * Requires cipher.size() = plain.size() + EXPANSION.
   */
  void Encrypt(std::span<const std::byte> plain, std::span<const std::byte> aad,
               Nonce96 nonce, std::span<std::byte> cipher) noexcept;

  /**
   * Decrypt a message with a specified 96-bit nonce and aad. Returns true if
   * valid.
   *
   * Requires cipher.size() = plain.size() + EXPANSION.
   */
  bool Decrypt(std::span<const std::byte> cipher, std::span<const std::byte> aad,
               Nonce96 nonce, std::span<std::byte> plain) noexcept;
};

#endif // CUSTOMMUTATOR_CRYPTO_CHACHA20POLY1305_H
