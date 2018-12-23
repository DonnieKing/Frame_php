<?php
/**
 * Created by PhpStorm.
 * User: Administrator
 * Date: 2018/12/17 0017
 * Time: 11:50
 */

namespace app\admin\controller;
session_start();
use app\model\User;
use pig\core\Controller;

class Index extends Controller
{
     public function __construct()
     {
         parent::__construct();
     }

     //测试
    public function demo($name='DonnieKing',$age=21)
    {
        return '我是'.$name.',今年'.$age;
    }

    //演示Plates模板引擎的基本使用
    public function testView()
    {
        //变量
        $site = 'php中文网';

        //数组
        $course = ['php','java','python'];

        //对象
        $lecture = new \stdClass();
        $lecture->name='DonnieKing';
        $lecture->age = 21;
        $lecture->course = 'php';

        //测试是否能覆盖变量
        $this->assign('site',$site);
        $this->assign('course',$course);
        $this->assign('lecture',$lecture);

        //模板渲染
        $this->fetch(__DIR__.'/../view/index/testView.php');
    }

    //用户信息列表
    public function index()
    {
        $rows = (new User())->select('user',['id','name','dept','art','email','create_time'],[
            //搜索功能: 如果用户提交了搜索条件,则根据条件查询
        'dept[~]'=>isset($_POST['dept']) ?$_POST['dept']:null
            ]);

        //第一个参数 模板， 第二个参数：模板变量
        // admin是命名空间，index控制器下的index模板
        return $this->view->render('admin::index/index',[
            'rows'=>$rows,
            'title'=>'武林高手排行榜',
            'logUrl'=>'/frame/admin/index/login',     //登录
            'logoutUrl'=>'/frame/admin/index/logout',   //退出登录
            'indexUrl'=>'/frame/admin/index/index',   //回到首页
            'insUrl'=>'/frame/admin/index/insert',    //添加操作
            'editUrl'=>'/frame/admin/index/edit',      //编辑操作
            'delUrl'=>'/frame/admin/index/delete',    //删除操作
        ]);
    }

    //管理员登录
    public function login()
    {
        if($_SERVER['REQUEST_METHOD'] =='POST')
        {
            //验证用户
            $res = (new User())->get('admin',['name','email','password'],[
                'AND'=>[
                    'email'=>$_POST['email'],
                    'password'=>$_POST['password'],
                ]
            ]);

            if(false === $res)
            {
                echo "<script>alert('邮箱或密码不正确');location.href='/frame/admin/index/index';</script>";
            }
            else
            {
                $_SESSION['name'] = $res['name'];
                echo "<script>alert('登录成功');location.href='/frame/admin/index/index';</script>";
            }

        }
    }

    //管理员退出
    public function logout()
    {
        session_destroy();
        echo "<script>alert('退出成功');location.href='/frame/admin/index/index';</script>";
    }

    //添加数据:分二步: 1. 渲染出添加表单;  2. 将数据写入表中
    public function insert()
    {
        return $this->view->render('admin::index/insert',[
            'title'=>'添加记录',
            'url' => '/frame/admin/index/add'
        ]);
    }

    //执行添加记录的操作
    public function add()
    {
        if($_SERVER['REQUEST_METHOD'] == 'POST')
        {
            //执行添加操作
            (new User())->insert('user',[
                'name'=>$_POST['name'],
                'dept'=>$_POST['dept'],
                'art'=>$_POST['art'],
                'email'=>$_POST['email'],
                'create_time'=>time(),
            ]);

            echo "<script>alert('添加成功');location.href='/frame/admin/index/index';</script>";
        }
    }

    //编辑用户
    //1.渲染编辑模板
    public function edit($id='')
    {
        $row = (new User())->get('user',['id','name','dept','art','email'],['id'=>$id]);

        return $this->view->render('admin::index/edit',[
            'title'=>'编辑用户',
            'url'=>'/frame/admin/index/save',
            'row'=>$row,
        ]);
    }

    //保存修改的用户信息
    public function save($id)
    {
        if($_SERVER['REQUEST_METHOD'] == 'POST')
        {
            //执行修改操作
            (new User())->update('user',[
                'name'=>$_POST['name'],
                'dept'=>$_POST['dept'],
                'art'=>$_POST['art'],
                'email'=>$_POST['email'],
                'create_time'=>time(),
            ], ['id'=>$id]);

            echo "<script>alert('修改成功!');location.href='/frame/admin/index/index';</script>";
        }

    }

    public function delete($id)
    {
        (new User())->delete('user',['id'=>$id]);
        echo "<script>alert('删除成功!');location.href='/frame/admin/index/index';</script>";
    }
}