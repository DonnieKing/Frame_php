<?php
/**
 * 路由解析类
 * 1、路由解析
 * 2、请求分发
 */

namespace pig;


class Route
{
    //路由配置信息
    //protected $route = [];
    public $route = [];

    //PATHINFO
    protected $pathInfo = [];
    //public $pathInfo = [];
     //   ?m=module/c=controller/a=insert  GET
     //   pathInfo : 不再用字符串拼接， 使用：/module/controller/insert  ,有利于url的重写

    //URL参数
    protected $params = [];
    //public $params = [];

    //构造方法
    public function __construct($route)
    {
        //路由配置初始化
        $this->route = $route;
    }

    //解析路由
    public function parse($queryStr='')
    {
        //  例：admin/user/add/name/peter/age/30 转化为：
        //  $this->pathInfo['module'=>'admin','controller'=>'user','action'=>'add']
        //  参数数组： $this->param = ['name'=>'peter','age'=>30]

        //第一步：将查询字符串前后的'/'去掉，然后再按分隔符'/'拆分到数组中
        //统一处理变为小写，处理简洁
        $queryStr = trim(strtolower($queryStr),'/');
        //把字符串打散为数组
        $queryArr = explode('/',$queryStr);
        //用回调函数过滤数组中的元素
        //$queryArr = array_filter($queryArr);

        //第二步：解析出$queryArr数组中的内容（模块，控制器，操作，参数）
         switch(count($queryArr))
         {
             //没有参数，则使用默认的模块、控制器、操作
             case 0:
                 $this->pathInfo = $this->route;
                 break;
             //只有一个参数,除模块外,控制器和操作使用默认值
             case 1:
                 $this->pathInfo['module'] = $queryArr[0];
                 break;
             //二个参数,模块和控制器自定义,操作默认
             case 2:
                 $this->pathInfo['module'] = $queryArr[0];
                 $this->pathInfo['controller'] = $queryArr[1];
                 break;
             //三个参数, 模块/控制器/操作全部自定义
             case 3:
                 $this->pathInfo['module'] = $queryArr[0];
                 $this->pathInfo['controller'] = $queryArr[1];
                 $this->pathInfo['action'] = $queryArr[2];
                 break;
             //默认情况，对参数进行处理
             default:
                 $this->pathInfo['module'] = $queryArr[0];
                 $this->pathInfo['controller'] = $queryArr[1];
                 $this->pathInfo['action'] = $queryArr[2];
                 //从pathInfo数组的索引3,即第4个元素起,将剩余元素全部做为操作的参数获取
                 $arr = array_slice($queryArr,3);
                 //键值对必须成对出现,所以每次必须递增2
                 for($i=0;$i<count($arr);$i+=2)
                 {
                     //如果没有第二个参数,则放弃,确保键值一一对应
                     if(isset($arr[$i+1]))
                     {
                        $this->params[$arr[$i]] = $arr[$i+1];
                     }
                 }
                 break;
         }
         //返回当前类的实例,这样就可以实现链式调用,即直接用->调用另一方法,省去重复写对象
         return $this;
    }

    //请求分发
    public function dispatch()
    {
        //生成的带有命名空间的控制器类名称：app\模块\controller\控制器类
        //类名称应该与类文件所在的绝对路径一一对应，这样才可以实现自动映射，方便自动加载
        //模块名称
        $module = $this->pathInfo['module'];

        //控制器名称
        $controller = 'app\\' .$module .'\controller\\'. ucfirst($this->pathInfo['controller']);

        //操作名
        $action = $this->pathInfo['action'];

        //判断当前类中是否存在指定的操作,如果没有,就执行默认的操作方法
        if(!method_exists($controller,$action))
        {
            $action = $this->route['action'];
            echo '没有该方法';
            header('Location:/frame/demo2.php');
        }
        //将用户的请求分发到指定的控制器和对应的操作方法上
        return call_user_func_array([new $controller,$action],$this->params);
    }

    //获取pathinfo
    public function getPathInfo()
    {
        return $this->pathInfo;
    }
    //获取模块
    public function getModule()
    {
        return $this->pathInfo['module']? :$this->route['module'];
    }
    //获取控制器名称
    public function getController()
    {
        return 'app\\' .$this->getModule() .'\controller\\'. ucfirst($this->pathInfo['controller']) ;
    }


}


//测试路由
$queryStr = $_SERVER['QUERY_STRING'];
echo $queryStr;
echo '<hr>';
echo '<pre>';
print_r(explode('/',$queryStr));

$config = require 'config.php';
$route = new Route($config['route']);
$route->parse($queryStr);
//print_r($route->route);
//print_r($route->pathInfo);
//print_r($route->params);

//测试请求分发
require __DIR__.'/../app/admin/controller/Index.php';
echo $route->dispatch();