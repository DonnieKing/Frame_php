<?php
/**
 * 测试模板引擎：plates
 */

//使用composer类加载器
require __DIR__.'/vendor/autoload.php';

use League\Plates\Engine;

/**
 *实例化模板引擎类，参数就是模板文件所在的目录(view下面目录是控制器，一般一个控制器对应一个模板（比如welcome）)
 * 1、模板目录可以使用相对路径，也可以使用绝对路径，推荐绝对路径
 * 2、相对路径：/app/demo/view
 */

$templates = new Engine(__DIR__.'/app/demo/view');

/**
 * 模板渲染：render('模板名称','模板变量')
 */

echo $templates->render('index/welcome',['hello'=>'模板也可以这么玩！']);
