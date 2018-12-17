<!doctype html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport"
          content="width=device-width, user-scalable=no, initial-scale=1.0, maximum-scale=1.0, minimum-scale=1.0">
    <meta http-equiv="X-UA-Compatible" content="ie=edge">
    <title>模板目录</title>
</head>
<body>
<h2 style="color: red">
<!--    e是转义，防止有非法字符-->
    <?= $this->e($hello); ?>
</h2>
</body>
</html>