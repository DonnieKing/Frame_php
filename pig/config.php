<?php
/**
 * 配置文件：适用于整个应用
 * 采用php数组的方式返回数据
 */

return [

    //应用配置
    'app'=>[
        //调试开关
        'debug'=>true,
    ],

    //路由配置
    'route'=>[
        //默认模块
        'module'=>'admin',

        //默认控制器
         'controller'=>'Index',

        //默认操作
          'action' => 'index',
    ],

    //数据库配置
    'db'=>[
        //数据库类型
        'database_type'=>'mysql',

        //默认的数据库名称
        'database_name'=>'frame',

        //默认的主机名
        'server' => '127.0.0.1',

        //默认的用户名
        'username' => 'root',

        //用户密码
        'password' => '123456',

        //默认客户端的字符编码集
        'charset' => 'utf8',

        //默认服务端口号
        'port' => 3306,

    ],


];