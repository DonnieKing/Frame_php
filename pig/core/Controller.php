<?php
/**
 * 框架的控制器基类
 */

namespace pig\core;


class Controller
{
    //视图对象
    protected $view = null;

    //构造方法：实例化视图类
    public function __construct()
    {
        $this->view = new namespace\View();
        //配置模板引擎
        $this->config();
    }

    //视图模板引擎配置
    public function config()
    {
        //设置模板目录名称[可选]
        $this->view->setDirectory(ROOT_PATH.'/app/admin/view');

        //设置模板目录别名：命名空间
        $this->view->addFolder('admin',ROOT_PATH.'/app/admin/view');

        //设置前台目录名称[可选]
        $this->view->setDirectory(ROOT_PATH.'/app/home/view');

        //设置前台模板目录别名：命名空间
        $this->view->addFolder('home',ROOT_PATH.'/app/home/view');
    }

    //任何模板引擎都有两个核心的功能
    //1、模板赋值  2、渲染模板
    //1、模板赋值
    public function assign($name,$value)
    {
        $this->data[$name] = $value;
    }

    //2、渲染模板
    public function fetch($file)
    {
        //1、将容器数组中的元素（键值对）转化为变量
        // $data['price'] = 1000 ,  目标：$price = 1000
        // $data['arr'] = [1,2,3]   目标：$arr=[1,2,3]

        //将数组的键值对转为变量的名值对的过程,返回变量个数
        extract($this->data);

        //2、加载模板文件
        if(file_exists($file) && is_file($file))
        {
            require $file;
        }

    }
}