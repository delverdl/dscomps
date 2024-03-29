INCLUDEPATH += .

# Input
HDR_INSTALL += $$PWD/liblzma/api/lzma.h

HDR_INSTALL_API += $$PWD/liblzma/api/lzma/base.h \
                   $$PWD/liblzma/api/lzma/bcj.h \
                   $$PWD/liblzma/api/lzma/block.h \
                   $$PWD/liblzma/api/lzma/check.h \
                   $$PWD/liblzma/api/lzma/container.h \
                   $$PWD/liblzma/api/lzma/delta.h \
                   $$PWD/liblzma/api/lzma/filter.h \
                   $$PWD/liblzma/api/lzma/hardware.h \
                   $$PWD/liblzma/api/lzma/index.h \
                   $$PWD/liblzma/api/lzma/index_hash.h \
                   $$PWD/liblzma/api/lzma/lzma12.h \
                   $$PWD/liblzma/api/lzma/stream_flags.h \
                   $$PWD/liblzma/api/lzma/version.h \
                   $$PWD/liblzma/api/lzma/vli.h

msvc {
  HEADERS += $$PWD/msvc/config.h
  DEFINES += HAVE_CONFIG_H
} else {
  DEFINES += HAVE_CHECK_CRC32 HAVE_CHECK_CRC64 HAVE_CHECK_SHA256 HAVE_CPUID_H \
    HAVE_DECODERS HAVE_DECODER_ARM HAVE_DECODER_ARM64 HAVE_DECODER_ARMTHUMB \
    HAVE_DECODER_DELTA HAVE_DECODER_IA64 HAVE_DECODER_LZMA1 HAVE_DECODER_LZMA2 \
    HAVE_DECODER_POWERPC HAVE_DECODER_SPARC HAVE_DECODER_X86 HAVE_ENCODERS \
    HAVE_ENCODER_ARM HAVE_ENCODER_ARM64 HAVE_ENCODER_ARMTHUMB HAVE_ENCODER_DELTA \
    HAVE_ENCODER_IA64 HAVE_ENCODER_LZMA1 HAVE_ENCODER_LZMA2 HAVE_ENCODER_POWERPC \
    HAVE_ENCODER_SPARC HAVE_ENCODER_X86 HAVE_FUNC_ATTRIBUTE_CONSTRUCTOR \
    HAVE_IMMINTRIN_H HAVE_INTTYPES_H HAVE_LZIP_DECODER HAVE_MF_BT2 HAVE_MF_BT3  \
    HAVE_MF_BT4 HAVE_MF_HC3 HAVE_MF_HC4 HAVE_STDBOOL_H HAVE_STDINT_H HAVE_USABLE_CLMUL \
    HAVE_VISIBILITY=1 HAVE__BOOL HAVE__MM_MOVEMASK_EPI8 HAVE___BUILTIN_ASSUME_ALIGNED \
    HAVE___BUILTIN_BSWAPXX MYTHREAD_VISTA NDEBUG PACKAGE_BUGREPORT=\"xz@tukaani.org\" \
    PACKAGE_NAME=\"XZ\x20Utils\" PACKAGE_URL=\"https://tukaani.org/xz/\"
}

HEADERS += $$PWD/common/mythread.h \
           $$PWD/common/sysdefs.h \
           $$PWD/common/tuklib_common.h \
           $$PWD/common/tuklib_config.h \
           $$PWD/common/tuklib_cpucores.h \
           $$PWD/common/tuklib_integer.h \
           $$PWD/common/tuklib_physmem.h \
           $$PWD/liblzma/check/check.h \
           $$PWD/liblzma/check/crc32_table_be.h \
           $$PWD/liblzma/check/crc32_table_le.h \
           $$PWD/liblzma/check/crc64_table_be.h \
           $$PWD/liblzma/check/crc64_table_le.h \
           $$PWD/liblzma/check/crc_macros.h \
           $$PWD/liblzma/common/alone_decoder.h \
           $$PWD/liblzma/common/block_buffer_encoder.h \
           $$PWD/liblzma/common/block_decoder.h \
           $$PWD/liblzma/common/block_encoder.h \
           $$PWD/liblzma/common/common.h \
           $$PWD/liblzma/common/easy_preset.h \
           $$PWD/liblzma/common/filter_common.h \
           $$PWD/liblzma/common/filter_decoder.h \
           $$PWD/liblzma/common/filter_encoder.h \
           $$PWD/liblzma/common/index.h \
           $$PWD/liblzma/common/index_decoder.h \
           $$PWD/liblzma/common/index_encoder.h \
           $$PWD/liblzma/common/lzip_decoder.h \
           $$PWD/liblzma/common/memcmplen.h \
           $$PWD/liblzma/common/outqueue.h \
           $$PWD/liblzma/common/stream_decoder.h \
           $$PWD/liblzma/common/stream_flags_common.h \
           $$PWD/liblzma/delta/delta_common.h \
           $$PWD/liblzma/delta/delta_decoder.h \
           $$PWD/liblzma/delta/delta_encoder.h \
           $$PWD/liblzma/delta/delta_private.h \
           $$PWD/liblzma/lz/lz_decoder.h \
           $$PWD/liblzma/lz/lz_encoder.h \
           $$PWD/liblzma/lz/lz_encoder_hash.h \
           $$PWD/liblzma/lz/lz_encoder_hash_table.h \
           $$PWD/liblzma/lzma/fastpos.h \
           $$PWD/liblzma/lzma/lzma2_decoder.h \
           $$PWD/liblzma/lzma/lzma2_encoder.h \
           $$PWD/liblzma/lzma/lzma_common.h \
           $$PWD/liblzma/lzma/lzma_decoder.h \
           $$PWD/liblzma/lzma/lzma_encoder.h \
           $$PWD/liblzma/lzma/lzma_encoder_private.h \
           $$PWD/liblzma/rangecoder/price.h \
           $$PWD/liblzma/rangecoder/range_common.h \
           $$PWD/liblzma/rangecoder/range_decoder.h \
           $$PWD/liblzma/rangecoder/range_encoder.h \
           $$PWD/liblzma/simple/simple_coder.h \
           $$PWD/liblzma/simple/simple_decoder.h \
           $$PWD/liblzma/simple/simple_encoder.h \
           $$PWD/liblzma/simple/simple_private.h
           
SOURCES += $$PWD/common/tuklib_cpucores.c \
           $$PWD/common/tuklib_physmem.c \
           $$PWD/liblzma/check/check.c \
           $$PWD/liblzma/check/crc32_fast.c \
           $$PWD/liblzma/check/crc32_table.c \
           $$PWD/liblzma/check/crc64_fast.c \
           $$PWD/liblzma/check/crc64_table.c \
           $$PWD/liblzma/check/sha256.c \
           $$PWD/liblzma/common/alone_decoder.c \
           $$PWD/liblzma/common/alone_encoder.c \
           $$PWD/liblzma/common/auto_decoder.c \
           $$PWD/liblzma/common/block_buffer_decoder.c \
           $$PWD/liblzma/common/block_buffer_encoder.c \
           $$PWD/liblzma/common/block_decoder.c \
           $$PWD/liblzma/common/block_encoder.c \
           $$PWD/liblzma/common/block_header_decoder.c \
           $$PWD/liblzma/common/block_header_encoder.c \
           $$PWD/liblzma/common/block_util.c \
           $$PWD/liblzma/common/common.c \
           $$PWD/liblzma/common/easy_buffer_encoder.c \
           $$PWD/liblzma/common/easy_decoder_memusage.c \
           $$PWD/liblzma/common/easy_encoder.c \
           $$PWD/liblzma/common/easy_encoder_memusage.c \
           $$PWD/liblzma/common/easy_preset.c \
           $$PWD/liblzma/common/file_info.c \
           $$PWD/liblzma/common/filter_buffer_decoder.c \
           $$PWD/liblzma/common/filter_buffer_encoder.c \
           $$PWD/liblzma/common/filter_common.c \
           $$PWD/liblzma/common/filter_decoder.c \
           $$PWD/liblzma/common/filter_encoder.c \
           $$PWD/liblzma/common/filter_flags_decoder.c \
           $$PWD/liblzma/common/filter_flags_encoder.c \
           $$PWD/liblzma/common/hardware_cputhreads.c \
           $$PWD/liblzma/common/hardware_physmem.c \
           $$PWD/liblzma/common/index.c \
           $$PWD/liblzma/common/index_decoder.c \
           $$PWD/liblzma/common/index_encoder.c \
           $$PWD/liblzma/common/index_hash.c \
           $$PWD/liblzma/common/lzip_decoder.c \
           $$PWD/liblzma/common/microlzma_decoder.c \
           $$PWD/liblzma/common/microlzma_encoder.c \
           $$PWD/liblzma/common/outqueue.c \
           $$PWD/liblzma/common/stream_buffer_decoder.c \
           $$PWD/liblzma/common/stream_buffer_encoder.c \
           $$PWD/liblzma/common/stream_decoder.c \
           $$PWD/liblzma/common/stream_decoder_mt.c \
           $$PWD/liblzma/common/stream_encoder.c \
           $$PWD/liblzma/common/stream_encoder_mt.c \
           $$PWD/liblzma/common/stream_flags_common.c \
           $$PWD/liblzma/common/stream_flags_decoder.c \
           $$PWD/liblzma/common/stream_flags_encoder.c \
           $$PWD/liblzma/common/string_conversion.c \
           $$PWD/liblzma/common/vli_decoder.c \
           $$PWD/liblzma/common/vli_encoder.c \
           $$PWD/liblzma/common/vli_size.c \
           $$PWD/liblzma/delta/delta_common.c \
           $$PWD/liblzma/delta/delta_decoder.c \
           $$PWD/liblzma/delta/delta_encoder.c \
           $$PWD/liblzma/lz/lz_decoder.c \
           $$PWD/liblzma/lz/lz_encoder.c \
           $$PWD/liblzma/lz/lz_encoder_mf.c \
           $$PWD/liblzma/lzma/fastpos_table.c \
           $$PWD/liblzma/lzma/lzma2_decoder.c \
           $$PWD/liblzma/lzma/lzma2_encoder.c \
           $$PWD/liblzma/lzma/lzma_decoder.c \
           $$PWD/liblzma/lzma/lzma_encoder.c \
           $$PWD/liblzma/lzma/lzma_encoder_optimum_fast.c \
           $$PWD/liblzma/lzma/lzma_encoder_optimum_normal.c \
           $$PWD/liblzma/lzma/lzma_encoder_presets.c \
           $$PWD/liblzma/rangecoder/price_table.c \
           $$PWD/liblzma/simple/arm.c \
           $$PWD/liblzma/simple/arm64.c \
           $$PWD/liblzma/simple/armthumb.c \
           $$PWD/liblzma/simple/ia64.c \
           $$PWD/liblzma/simple/powerpc.c \
           $$PWD/liblzma/simple/simple_coder.c \
           $$PWD/liblzma/simple/simple_decoder.c \
           $$PWD/liblzma/simple/simple_encoder.c \
           $$PWD/liblzma/simple/sparc.c \
           $$PWD/liblzma/simple/x86.c
