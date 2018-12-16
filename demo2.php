<?php
/**
 * 测试数据库框架：Medoo
 */

/**
 * Composer准备工作：
 * 1、加载composer的类库自动加载器：vendor/autoload.php
 * 2、配置一下Medoo
 */

//使用Composer自动加载器
require __DIR__.'/vendor/autoload.php';

//导入配置文件
$config = require __DIR__.'/pig/config.php';

//导入Medoo命名空间
use Medoo\Medoo;

$db = new Medoo($config['db']);

$rows = $db->select('user',['id','name','dept','art','email']);

echo '<pre>'.print_r($rows,true);