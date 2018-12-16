<?php
/**
 * 测试模板引擎：plates
 */

//使用composer类加载器
require __DIR__.'/vendor/autoload.php';

use League\Plates\Engine;

/**
 *实例化模板引擎类，参数就是模板文件所在的目录
 * 1、模板目录可以使用相对路径，也可以使用绝对路径，推荐绝对路径
 * 2、相对路径：/app/demo/view
 */

