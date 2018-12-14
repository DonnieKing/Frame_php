<?php
/**
 * $_SERVER
 * call_user_func_array()
 */

//echo '<pre>'.print_r($_GET,true);
// [admin/user/add/name/peter/age/30/sex/0] =>

// url：  http://127.0.0.1/frame/demo1.php?admin/user/add/name/peter/age/30/sex/0

//echo $_SERVER['QUERY_STRING'].'<br>';
//   admin/user/add/name/peter/age/30/sex/0

//echo $_SERVER['REQUEST_URI'].'<br>';
//   /frame/demo1.php?admin/user/add/name/peter/age/30/sex/0

/**
 *  user/add/name/peter/age/30/sex/0
 *  user:控制器  User.php
 *  add: User.php中的一个add
 *  name/peter/age/30/sex/0  参数：name=peter,age=30,sex=0
 */

//$user = new User();
//$user->add($name,$age,$sex);


namespace demo;

//call_user_func_array() :执行一个用户回调函数
function hello( $name ='小茗同学')
{
    echo 'hello，'.$name.'，请开始你的表演';
}
//如何执行这个函数？
//1、按函数名称来访问
echo hello().'<br>';
echo hello('胖虎').'<br>';
//2、由系统函数call_user_func_array()来调用
echo call_user_func_array('demo\hello',['悟空']);   //如果要使用默认参数： call_user_func_array('demo\hello',[]);
echo '<br>';
//用常量来替换命名空间的名称
echo call_user_func_array(__NAMESPACE__.'\hello',['八戒']).'<br>';

//3、如果将函数作为类中的一个成员方法，能不能使用call_user_func_array()来执行
class Demo{

     //普通方法
     public function hello($name ='小茗同学')
     {
         echo  'hello，'.$name.'，你又调皮啦！';
     }
     //静态方法
    public static function getDream($dream = '最有钱')
    {
        echo  'DonnieKing要成为世界上'.$dream.'的人';
    }
}

//3.1、调用类中的普通方法
$demo = new Demo();
//第一个参数必须使用数组格式，call_user_func_array(['类或对象','方法名称'],['参数'])
echo call_user_func_array([$demo,'hello'],['DonnieKing']).'<br>';
//简化一下
echo call_user_func_array([(new Demo()),'hello'],['WANGCHU']).'<br>';

//3.2、调用类中的静态方法 (类名，方法)
echo call_user_func_array([__NAMESPACE__.'\demo','getDream'],['最有梦想']);


/**
 * 从URL地址中解析出：控制器类和对应的方法:$SERVER['QUERY_STRING']
 * 在调用call_user_func_array(['控制器类','操作方法'],['参数列表']);
 */
