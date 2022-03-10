# Git_note  
- [Git_note](#git_note)
  - [create repository](#create-repository)
  - [add file and commit](#add-file-and-commit)
  - [commands](#commands)
  - [版本回退](#版本回退)
  - [删除文件](#删除文件)
  - [远程仓库](#远程仓库)
    - [将本地git推给Github](#将本地git推给github)
    - [删除远程库](#删除远程库)
    - [从远程库克隆到本地](#从远程库克隆到本地)
  - [分支](#分支)
  - [标签](#标签)
## create repository  
```
$ mkdir <name_dir>
$ cd <name_dir>
$ git init
```
## add file and commit  
```
$ git add <name_file>   
$ git commit -m "messages"  
```
## commands
```
$ git status // get the status of repository
$ git diff	//查看工作区和暂存区差异
$ git diff --cached	//查看暂存区和仓库差异
$ git diff HEAD //查看工作区和仓库的差异
$ git diff --stat //显示摘要而非整个 diff
$ git diff <file> // get the difference 
$ git log //查看最近git修改日志
$ git log --pretty=oneline //查看简短的git修改日志
$ git reflog //记录版本变化的id
```
## 版本回退  
```
如果已经commit
$ git reset --hard Head^  //回退上一个版本
$ git reset --hard~<id>   //回到id的版本
如果没有commit，但是add
$ git reset Head <file> //撤销暂存区，然后回到上一步
$ git checkout -- <file> //其实就是用版本库里的文件替换工作区文件
如果没有commit，且没有add
$ git checkout -- <file>  //丢弃工作区的修改，如果add后修改，则回到暂存区的状态，如果没add就修改，则回到工作区修改前的样子
```
## 删除文件
```
$ rm <file>
$ git rm <file>
$ git commit -m 'message'
如果删除错误，想回退
$ rm <file>
$ git checkout  -- <file>
如果已经git rm 
$ rm <file>
$ git rm <file>
$ git reset Head <file>
$ git checkout -- <file>
如果已经commit
$ rm <file>
$ git rm <file>
$ git commit -m 'message'
$ git reset --hard Head^  //回退上一个版本
```
## 远程仓库
建立github账户
创建SSH Key。

> 在用户主目录下，看看有没有.ssh目录，如果有，再看看这个目录下有没有`id_rsa`和`id_rsa.pub`这两个文件，如果已经有了，可直接跳到下一步。
>
> 如果没有，打开Shell（Windows下打开Git Bash），创建SSH Key：
> 一路回车，使用默认值即可，一般无需设置密码。
>
> ```
> $ ssh-keygen -t rsa -C "youremail@example.com"
> ```
>
> 如果一切顺利的话，可以在用户主目录里找到`.ssh`目录，里面有`id_rsa`和`id_rsa.pub`两个文件，这两个就是SSH Key的秘钥对，`id_rsa`是私钥，不能泄露出去，`id_rsa.pub`是公钥，可以放心地告诉任何人。
>
> 之后将id_rsa.pub输入到github中
>
> 进行验证是否成功,在git bash下输入`ssh -T git@github.com`


### 将本地git推给Github
第一次
```
git remote add origin git@github.com:... //添加远程库 origin
```

```
$ git push -u origin master //将本地master分支推给远程库origin
```
以后
```
$ git push origin master
```
### 删除远程库
```
$ git remote -v //查看远程库信息
$ git remote rm origin //删除远程库与本地库的联系
```

### 从远程库克隆到本地  

```
$ git clone git@github.com:... //也可以使用https协议，比较慢
```

## 分支

```
$ git branch //查看分支
$ git branch <name> //创建分支
$ git checkout <name>或者git switch <name> //切换分支
$ git checkout -b <name>或者`git switch -c <name>` //创建并切换分支
$ git merge <name> //合并某分支到当前分支
$ git branch -d <name> //删除分支

// 当Git无法自动合并分支时，就必须首先解决冲突。解决冲突后，再提交，合并完成。解决冲突就是把Git合并失败的文件手动编辑为我们希望的内容，再提交。
$ git log --graph //查看分支合并图。
```

## 标签

```
$ git tag <tagname> //先切换到需要打标签的分支上，打一个新标签
$ git tag //可以查看所有标签
$ git tag v1.0
$ git tag v0.9 f52c633 //对历史提交的commit打标签
$ git show <tagname> //查看标签信息
$ git tag -a <tagname> -m "message" 可以指定标签信息
```

