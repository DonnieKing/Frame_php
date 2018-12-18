<?php
/**
 * 框架基础类
 * 1.调试模式
 * 2.自动加载
 * 3.启动框架
 */

namespace pig;


class Base
{
    //框架配置
    protected $config = [];

    //路由信息
    protected $queryStr = '';

    //构造方法
    public function __construct($config,$queryStr='')
    {
        $this->config = $config;
        $this->queryStr = $queryStr;
    }

    //设置调试模式
    public function setDebug()
    {
        //debug == true
        if($this->config['app']['debug'])
        {
            error_reporting(E_ALL);
            ini_set('display_errors','On');
        }
        else
        {
            //error_reporting(E_ALL);
            ini_set('display_errors','Off');
            ini_set('log_errors','On');
        }
    }

    //注册自动加载器：自动加载的是类
    public function loader($class)
    {
        // new \app\admin\controller\Stu() ,   app/admin/controller/Stu.php
        // new Stu()
        // $class == \app\admin\controller\Stu
        // /app/admin/controller/Stu
        $path = ROOT_PATH.str_replace('\\','/',$class).'.php';

        //如果没有找到类文件，就直接返回默认首页
        if(!file_exists($path))
        {
            header('Location: /');
        }

        require $path;
    }


    //启动框架
    public function run()
    {
        //调试模式
        $this->setDebug();

        //自动加载
        spl_autoload_register([$this,'loader']);

        //请求分发
        echo (new Route($this->config['route']))->parse($this->queryStr)->dispatch();
    }
}

