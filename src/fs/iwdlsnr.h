#pragma once
#ifndef IWDLSNR_H
#define IWDLSNR_H

#include "basedefs.h"
#include <unistd.h>
#include <stdbool.h>

IW_EXTERN_C_START

/**
 * @brief File data events listener.
 */
typedef struct IWDLSNR {

  /**
   * @brief Before file open event.
   *
   * @param path File path
   * @param mode File open mode same as in open(2)
   */
  iwrc(*onopen)(struct IWDLSNR *self, const char *path, int mode);

  /**
   * @brief After file closed.
   */
  iwrc (*onclosed)(struct IWDLSNR *self, const char *path);

  /**
   * @brief Write @a val value starting at @a off @a len bytes
   */
  iwrc(*onset)(struct IWDLSNR *self, off_t off, uint8_t val, uint64_t len, int flags);

  /**
   * @brief Copy @a len bytes from @a off offset to @a noff offset
   */
  iwrc(*oncopy)(struct IWDLSNR *self, off_t off, uint64_t len, off_t noff, int flags);

  /**
   * @brief Write @buf of @a len bytes at @a off
   */
  iwrc(*onwrite)(struct IWDLSNR *self, off_t off, const void *buf, uint64_t len, int flags);

  /**
   * @brief File need to be resized.
   *
   * @param osize Old file size
   * @param nsize New file size
   * @param [out] handled File resizing handled by llistener.
   */
  iwrc(*onresize)(struct IWDLSNR *self, uint64_t osize, uint64_t nsize, int flags);

  /**
   * @brief File sync successful
   */
  iwrc(*onsynced)(struct IWDLSNR *self, int flags);

} IWDLSNR;

IW_EXTERN_C_END

#endif // !IWDLSNR_H