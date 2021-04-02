<?php
declare(strict_types=1);
$cfg['blowfish_secret'] = 'lregenarlregenar';
$i = 1;
$cfg['Servers'][$i]['auth_type'] = 'cookie';
$cfg['Servers'][$i]['host'] = 'mysql';
$cfg['Servers'][$i]['port'] = '3306';
$cfg['Servers'][$i]['compress'] = false;
$cfg['Servers'][$i]['AllowNoPassword'] = true;
$cfg['Servers'][$i]['user'] = 'lregenar';
$cfg['Servers'][$i]['password'] = 'lregenar';
$cfg['Servers'][$i]['compress'] = false;
$cfg['UploadDir'] = '';
$cfg['SaveDir'] = '';