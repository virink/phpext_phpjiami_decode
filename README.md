# phpjiami_decode

An ext for php to decode some phpjiami

## Download

    cd /path/to/php-src/ext/
    git clone https://github.com/virink/phpext_phpjiami_decode.git ./phpjiami_decode
    cd phpjiami_decode

## Install

    phpize
    ./configure
    make
    make install

## Config

    echo "" >> /etc/php.ini
    echo "[phpjiami_decode]" >> /etc/php.ini
    echo "extension=phpjiami_decode.so" >> /etc/php.ini

## Usage

    cd /path/to/your/web/
    php -S localhost:8000

Then, when you request _http://localhost:8000/xxx.php_

If `eval` in the `xxx.php` and it ran, the eval's parameter will save to `/tmp/phpjiami_decode_file.php`.

## LICENSE

[MIT](LICENSE)

## Thanks

> [evalhook](https://github.com/bizonix/evalhook)