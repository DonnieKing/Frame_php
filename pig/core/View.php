<?php
/**
 * 框架的视图基类
 * 1、使用第三方的一个基于原生php的模板引擎：Plates
 */

namespace pig\core;
use League\Plates\Engine;


class View  extends Engine
{

   //变量容器
   protected $data = [];

   //构造方法

    /**
     * View constructor.
     * @param null $directory 模板默认目录
     * @param string $fileExtension 模板默认扩展名：php
     */
    public function  __construct($directory = null, $fileExtension = 'php')
    {
        parent::__construct($directory, $fileExtension);
    }
}