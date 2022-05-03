# This is an example PKGBUILD file. Use this as a start to creating your own,
# and remove these comments. For more information, see 'man PKGBUILD'.
# NOTE: Please fill out the license field for your package! If it is unknown,
# then please put 'unknown'.

# Maintainer: Ervin Pektor <pektor DOT ervin AT sch DOT bme DOT hu>
pkgname=factolog
pkgver=1
pkgrel=1
pkgdesc="Factolog compiler"
arch=('x86_64')
url="https://github.com/Erv00"
license=('unknown')
groups=()
depends=("gcc-libs")
makedepends=()
checkdepends=()
optdepends=()
provides=()
conflicts=()
replaces=()
backup=()
options=()
source=("factolog.tar.gz" "CMakeLists.txt")
noextract=()
md5sums=("2b27567651aea869540d2fb6ebca5a1d" "947e0207098c06af5a1a0546d4c22085")
validpgpkeys=()

build() {
	echo "$pkgdir" "$srcdir"
	mkdir -p "$pkgname-build"
	cd "$pkgname-build"
	cmake ..
	make
}

package() {
	cd "$pkgname-build"
	cmake --install . --prefix "$pkgdir/usr"
}
