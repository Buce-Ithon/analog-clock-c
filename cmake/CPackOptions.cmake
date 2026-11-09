# 1. 安装可执行文件到 bin 目录（或者根目录）
install(TARGETS analog-clock
    RUNTIME DESTINATION .
)

# 2. 如果你的依赖库有 raylib.dll，或者其他运行时 DLL，可以一并安装
install(FILES $<TARGET_RUNTIME_DLLS:analog-clock>
    DESTINATION .
)
# 如果上面没有自动抓取到 raylib.dll，也可以显式指定：
# install(FILES D:/Projects/lib/raylib-5.5_win64_msvc16/lib/raylib.dll DESTINATION .)

# 3. 安装 assets 资源文件夹到包中的 assets 目录
install(DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/clock/assets"
    DESTINATION .
)

# --- CPack 打包配置 ---
set(CPACK_PACKAGE_NAME "Analog Clock")
set(CPACK_PACKAGE_VENDOR "Buce-Ithon")
set(CPACK_PACKAGE_VERSION "1.0.0")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "A desktop analog clock toy built with C and Raylib")

# 选择你要生成的打包格式，Windows 上常用 ZIP 或 NSIS（安装包）
# 如果只需要压缩包，保留 "ZIP" 即可；如果想要类似双击安装的 .exe 安装程序，可以加上 "NSIS"
set(CPACK_GENERATOR "ZIP")

# 引入 CPack 模块（必须放在最后）
include(CPack)