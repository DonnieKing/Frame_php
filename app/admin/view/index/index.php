<!doctype html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport"
          content="width=device-width, user-scalable=no, initial-scale=1.0, maximum-scale=1.0, minimum-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <link rel="stylesheet" href="/frame/static/css/style.css">

    <title><?=$this->e($title)?></title>
</head>
<body>

<?php if(isset($_SESSION['name']) && $_SESSION['name'] == 'admin'):?>
    <p>欢迎管理员：<?=$this->e($_SESSION['name'])?> | <a href="<?=$this->e($logoutUrl) ?>">退出</a></p>
<?php else: ?>
<form action="<?=$this->e($logUrl) ?>" method="post">
    邮箱：<input type="email" name="email">
    密码：<input type="password" name="password">
    <button>登录</button>
</form>
<?php endif; ?>

        <table>
            <caption>武林高手登记表
                <small><a href="<?=$this->e($insUrl)?>">增加</a> </small>
            </caption>
            <tr>
                <th>ID</th>
                <th>姓名</th>
                <th>门派</th>
                <th>独门绝技</th>
                <th>邮箱</th>
                <th>创建时间</th>
                <?php if(isset($_SESSION['name']) && $_SESSION['name'] == 'admin'):?>
                <th>编辑</th>
                <?php endif; ?>
            </tr>
            <?php foreach($rows as $row):  ?>
                <tr>
                    <td><?=$this->e($row['id']) ?></td>
                    <td><?=$this->e($row['name']) ?></td>
                    <td><?=$this->e($row['dept']) ?></td>
                    <td><?=$this->e($row['art']) ?></td>
                    <td><?=$this->e($row['email']) ?></td>
                    <td><?=$this->e(date('Y-m-d H:i:s',$row['create_time'])) ?></td>
                    <?php if(isset($_SESSION['name']) && $_SESSION['name'] == 'admin'):?>
                    <td>
                        <a href="<?=$this->e($editUrl)?>/id/<?=$this->e($row['id']) ?>">修改</a>&nbsp;&nbsp;&nbsp;
                        <a href="<?=$this->e($delUrl) ?>/id/<?=$this->e($row['id']) ?>">删除</a>
                    </td>
                    <?php endif; ?>

                </tr>
            <?php endforeach; ?>
        </table>



</body>
</html>