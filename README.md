# plasma-hello-counter

A small KDE Plasma 6 widget with a C++ part: a button that counts clicks.
It is the companion code of the blog post
[Your first Plasma 6 widget: C++, QML and the Observer pattern](https://ilmanzo.github.io/post/your-first-plasma-6-widget/),
written to celebrate the 30th birthday of KDE.

```
src/counter.{h,cpp}                    C++ model: a count, a countChanged() signal, increment()/reset() slots
package/contents/ui/main.qml           QML view and controller
package/metadata.json                  widget identity
autotests/countertest.cpp              Qt Test: do the signals fire?
CMakeLists.txt                         builds the QML module, installs everything
```

## Build and install

openSUSE Tumbleweed:

```bash
sudo zypper in cmake gcc-c++ kf6-extra-cmake-modules qt6-qml-devel qt6-test-devel
```

Debian 13:

```bash
sudo apt install cmake g++ make extra-cmake-modules qt6-declarative-dev qt6-base-dev
```

Fedora:

```bash
sudo dnf install cmake gcc-c++ make extra-cmake-modules qt6-qtdeclarative-devel qt6-qtbase-devel
```

(All three lists build, test and install the project in a clean container.)

```bash
cmake -B build -DCMAKE_INSTALL_PREFIX=~/.local
cmake --build build --parallel
ctest --test-dir build --output-on-failure
cmake --install build
```

## Run it

The widget has two parts: the QML package, which Plasma finds in `~/.local/share/plasma/plasmoids`, and the C++
module `org.opensuse.hellocounter`, which is installed in `<prefix>/lib64/qml`. Qt only searches its own system
directories for QML modules, so for an install under `~/.local` you must set `QML_IMPORT_PATH`. Without it the
widget fails with:

```
module "org.opensuse.hellocounter" is not installed
```

The right value is the `qml` directory that `cmake --install` just printed (it also prints a reminder at the end):
`~/.local/lib64/qml` on openSUSE and Fedora, `~/.local/lib/x86_64-linux-gnu/qml` on Debian and Ubuntu.

### Quick try, in a standalone window

```bash
env QML_IMPORT_PATH=$HOME/.local/lib64/qml plasmawindowed org.opensuse.hellocounter
```

`env VAR=value command` works the same in bash and fish. Add `QT_FORCE_STDERR_LOGGING=1` to see QML errors in the
terminal (otherwise Qt sends them to the journal). `plasmawindowed` is single-instance: if a window for this widget
is already open, a second run hands over to it and exits.

### In the panel or on the desktop

`plasmashell` is started by your session, not by your shell, so a variable exported in a terminal does not reach it.
Put it where the session reads it, then log out and in again:

```bash
mkdir -p ~/.config/plasma-workspace/env
echo 'export QML_IMPORT_PATH=$HOME/.local/lib64/qml' > ~/.config/plasma-workspace/env/hello-counter.sh
```

Then right-click the desktop or a panel, choose *Add or manage widgets…* and search for "Hello counter".

A system-wide install (`-DCMAKE_INSTALL_PREFIX=/usr`, or an RPM) needs none of this: Qt already searches there.

## License

GPL-2.0-or-later, see [LICENSE](LICENSE).
