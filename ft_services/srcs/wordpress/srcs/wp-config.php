<?php
define( 'DB_NAME', 'lregenar' );
define( 'DB_USER', 'lregenar' );
define( 'DB_PASSWORD', 'lregenar' );
define( 'DB_HOST', 'mysql:3306' );
define( 'WP_HOME', 'http://192.168.99.101:5050' );
define( 'WP_SITEURL', 'http://192.168.99.101:5050' );
define( 'DB_CHARSET', 'utf8' );
define( 'DB_COLLATE', '' );
define('FS_METHOD', 'direct');
// https://api.wordpress.org/secret-key/1.1/salt/
define('AUTH_KEY',         '2z0zJ]:ar~vlfx0.2^-.|=e};QEcO~^G9hAW-if.)9:k @$G?y*V32wJF$8ez1Dr');
define('SECURE_AUTH_KEY',  '%ExnrF?ww9<> @LNpj-38xgJjMmj$aTXLO<sUAD/sKpHh8] {qhOob.|H|3rrI53');
define('LOGGED_IN_KEY',    '4mi*:fB~ .yHW-QzPYJl#D*x<p+V,a .tL-AUP-+6j~@t|m?*~k84+!=-Y#H2UK:');
define('NONCE_KEY',        '_Sjs];&6qTWa=Cy8CDiZnONO%rM2w-L&y[ob;dqHDckUueDMQS`51$BaV?X%rTFF');
define('AUTH_SALT',        'dPd;| H|-*nHW31XVUtcdWomh+IeRB,m[-&7K.;Uc-,MFZ%F]|3>zfszN1}ajZq}');
define('SECURE_AUTH_SALT', 'UMfN0V0:gC?eCGxaYFP=i%6(-@@;4m<enoD]|;HII*h7iK .nbL +/x&,[g]!cf9');
define('LOGGED_IN_SALT',   'x]R7J*Lsb(-j`I5K7D#Ok>P7<CgI=rAG6^z-Mf*ONaAV_|EpTa2~$&(P6i5D;e>y');
define('NONCE_SALT',       'hrjQuVSDBZv@n/{[r<|<(X*CGKgZNW,d-FH{X0KxxmioZNZ)wv0VGv1d|a1LG[kF');

$table_prefix = 'wp_';
define( 'WP_DEBUG', true );
if ( ! defined( 'ABSPATH' ) ) {
	define( 'ABSPATH', __DIR__ . '/' );
}
require_once ABSPATH . 'wp-settings.php';