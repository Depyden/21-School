<?php
/**
 * The base configuration for WordPress
 *
 * The wp-config.php creation script uses this file during the
 * installation. You don't have to use the web site, you can
 * copy this file to "wp-config.php" and fill in the values.
 *
 * This file contains the following configurations:
 *
 * * MySQL settings
 * * Secret keys
 * * Database table prefix
 * * ABSPATH
 *
 * @link https://wordpress.org/support/article/editing-wp-config-php/
 *
 * @package WordPress
 */

// ** MySQL settings - You can get this info from your web host ** //
/** The name of the database for WordPress */
define( 'DB_NAME', 'wordpress' );

/** MySQL database username */
define( 'DB_USER', 'lregenar' );

/** MySQL database password */
define( 'DB_PASSWORD', 'lregenar21' );

/** MySQL hostname */
define( 'DB_HOST', 'localhost' );

/** Database Charset to use in creating database tables. */
define( 'DB_CHARSET', 'utf8' );

/** The Database Collate type. Don't change this if in doubt. */
define( 'DB_COLLATE', '' );

/**#@+
 * Authentication Unique Keys and Salts.
 *
 * Change these to different unique phrases!
 * You can generate these using the {@link https://api.wordpress.org/secret-key/1.1/salt/ WordPress.org secret-key service}
 * You can change these at any point in time to invalidate all existing cookies. This will force all users to have to log in again.
 *
 * @since 2.6.0
 */
define('AUTH_KEY',         '2qczW3+V:aauJq0R@k@~luL(S4AE n)&58R**fv+d2yU-{(UO8oVM_<AN~JI]PPR');
	define('SECURE_AUTH_KEY',  'HE %p/&Uf<[+ *n/dW70$I1i{p4^qB/ZEKi5xu0OiEs+xO+P%VbLFrIg4Uyd2pYA');
	define('LOGGED_IN_KEY',    'o,.Ei7_aSG8tU!QVLP9+TVLPmX7ADSa-6BuqOaO5&+[nZt^f0SK-`A8+9sZz;Z6r');
	define('NONCE_KEY',        '4cI8%8lm9xsL5!LwU_h)Kr$ti+yoS_Rp:b&20?Q#A{z{$v`zEF=xS.22y3a+z(*,');
	define('AUTH_SALT',        'OD.y@s{5?F5^)(XUfj3{qZe]CCqqe+9-V. [-(MCH(_?PJVhNk1dPhZ+_Y<(Q5s1');
	define('SECURE_AUTH_SALT', '3O45]nlI_3oTedEQD~|uA0KK~.cSm95+nTsg<L=x&U#s+O Q[tt+ u2zYgB572)n');
	define('LOGGED_IN_SALT',   'x5`si|dPu.Mc+o<8d4az}Bmu.n|UXM4~ck,<iQ7H~t*+kG}(ZIn ,Y26:dXLCQC+');
	define('NONCE_SALT',       'c|])O|yI$.*/%^I 37d~T/pwm~L,JXg?!>Y= f0lfI,qe|~ub?9>(ESu9FJfjH)Z');
	
/**#@-*/

/**
 * WordPress Database Table prefix.
 *
 * You can have multiple installations in one database if you give each
 * a unique prefix. Only numbers, letters, and underscores please!
 */
$table_prefix = 'wp_';

/**
 * For developers: WordPress debugging mode.
 *
 * Change this to true to enable the display of notices during development.
 * It is strongly recommended that plugin and theme developers use WP_DEBUG
 * in their development environments.
 *
 * For information on other constants that can be used for debugging,
 * visit the documentation.
 *
 * @link https://wordpress.org/support/article/debugging-in-wordpress/
 */
define( 'WP_DEBUG', false );

/* That's all, stop editing! Happy publishing. */

/** Absolute path to the WordPress directory. */
if ( ! defined( 'ABSPATH' ) ) {
	define( 'ABSPATH', __DIR__ . '/' );
}

/** Sets up WordPress vars and included files. */
require_once ABSPATH . 'wp-settings.php';
