#
# Copyright (c) 2019 Nordic Semiconductor
#
# SPDX-License-Identifier: LicenseRef-Nordic-5-Clause
#

zephyr_sources(spm.c)
zephyr_sources_ifdef(CONFIG_SPM_SECURE_SERVICES secure_services.c)
zephyr_sources_ifdef(CONFIG_SPM_SHARE_CONSOLE_UART spm_uart.c)
zephyr_linker_sources(SECTIONS secure_services.ld)

if(CONFIG_ARM_FIRMWARE_HAS_SECURE_ENTRY_FUNCS)
  set_shared(IMAGE ${IMAGE_NAME} APPEND PROPERTY BUILD_BYPRODUCTS
        ${CMAKE_BINARY_DIR}/${CONFIG_ARM_ENTRY_VENEERS_LIB_NAME}
  )
endif()
