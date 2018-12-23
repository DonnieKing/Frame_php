<!doctype html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport"
          content="width=device-width, user-scalable=no, initial-scale=1.0, maximum-scale=1.0, minimum-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <title><?= $this->e($title)?></title>
</head>
<body>
<style>
    table{
        width: 300px;
        height: 250px;
        background: lightskyblue;
        border: 1px solid lightgray;
        padding: 20px;
        margin: 50px auto;
        box-shadow: 2px 2px 2px #888;
        border-radius: 3px;
    }
    table caption{
        font-size: 1.5em;
        margin-bottom: 10px;
    }
    table tr td:first-child{
        text-align: center;
    }
    table button{
        width:100px;
        height:30px;
        background: aquamarine;
        border: none;
    }
    table button:hover{
        background: lightseagreen;
        cursor:pointer;
    }
</style>
<form action="<?=$this->e($url)?>/id/<?=$this->e($row['id']) ?>" method="post">

    <table>
        <caption>添加用户信息</caption>

        <tr>
            <td><label for="name">用户名：</label></td>
            <td><input type="text" name="name" id="name" value="<?=$row['name'] ?>" required></td>
        </tr>
        <tr>
            <td><label for="dept">所属帮派：</label></td>
            <td><input type="text" name="dept" id="dept" value="<?=$row['dept'] ?>" required></td>
        </tr>
        <tr>
            <td><label for="art">独门绝技：</label></td>
            <td><input type="text" name="art" id="art" value="<?=$row['art'] ?>"  required></td>
        </tr>
        <tr>
            <td><label for="email">用户邮箱：</label></td>
            <td><input type="text" name="email" id="email" value="<?=$row['email'] ?>"  required></td>
        </tr>
        <tr>
            <td colspan="2" align="center"><button>修改</button></td>
        </tr>
    </table>

</form>
</body>
</html>