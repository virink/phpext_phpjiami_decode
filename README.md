# phpjiami_decode

An extension for php to decode some phpjiami and extcrypt

- [x] phpjiami
- [x] extcrypt
- [ ] OPCode

## Support version

**PHP 5.6**(just test myself)

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

    最好是最优先加载，也就是放在ini最前面。。。(这个是经验，但是不能保证一定)

## Usage

    cd /path/to/your/web/
    php -S localhost:8000

Then, when you request _http://localhost:8000/xxx.php_

If `eval` in the `xxx.php` and it ran, the eval's parameter will save to `/path/for/your/dir/xxx.eval.php`.

### e.g:

    /var/www/html/index.php
    /var/www/html/index.eval.php or /tmp/index.php.crypt.php

## LICENSE

[MIT](LICENSE)

## Thanks

> [evalhook](https://github.com/bizonix/evalhook)