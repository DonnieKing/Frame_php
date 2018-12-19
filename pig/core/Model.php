<?php
/**
 * 框架的模型基类
 * 1.采用Medoo作为数据库管理的框架
 * 2.Medoo是一个轻量级的基于PDO预处理，与类型无关的数据库框架
 */

namespace pig\core;

//引入Medoo框架类的命名空间
use Medoo\Medoo;

class Model extends Medoo
{
    public function __construct($options=null)
    {
        //导入配置文件
        $config = require __DIR__.'/../config.php';
        $options = $config['db'];

        //实例化数据库框架Medoo
        parent::__construct($options);
    }
}