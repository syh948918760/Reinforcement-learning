### Policy Gradient

#### 1. 主要思想

输入：状态
输出：Action

Policy Gradients 直接输出动作的最大好处就是, 它能在一个连续区间内挑选动作

而基于值的, 比如 Q-learning, 它如果**在无穷多的动作中计算价值**, 从而选择行为, 不太可行

#### 2. 算法

policy gradient 的第一个算法是一种基于 **整个回合(多步)数据** 的更新, 也叫 **REINFORCE** 方法. 这种方法是 policy gradient 的最基本方法, 有了这个的基础, 我们再来做更高级的.

[![Policy Gradients 算法更新 (Tensorflow)](https://morvanzhou.github.io/static/results/reinforcement-learning/5-1-1.png)](https://morvanzhou.github.io/static/results/reinforcement-learning/5-1-1.png)

`delta(log(Policy(s,a))*V)` 表示在 状态 `s` 对所选动作 `a` 的吃惊度, 
如果 `Policy(s,a)`概率越小, 反向的 `log(Policy(s,a))` (即 `-log(P)`) 反而越大. 

如果在 `Policy(s,a)` 很小的情况下, 拿到了一个 大的 `R`, 也就是 大的 `V`, 

那 `-delta(log(Policy(s, a))*V)` 就更大, 表示更吃惊, 

(我选了一个不常选的动作, 却发现原来它能得到了一个好的 reward, 那我就得对我这次的参数进行一个大幅修改). 



#### 2. 如何反向传递

Policy神经网络

![](https://morvanzhou.github.io/static/results/reinforcement-learning/5-2-1.png)

没有值（没有loss）如何反向传递？

1. 观测的信息通过神经网络分析, 选出了左边的行为, 我们直接进行反向传递, 使之下次被选的可能性增加。

2. Reward

   2.1 这次的行为是不好的 那我们的动作可能性增加的幅度 随之被减低

   2.2 我们这是好行为, 那我们就在这次反向传递的时候加大力度, 让它下次被多选的幅度更大

这样就能靠Reward来左右我们的神经网络反向传递。



为了确保这个动作真的是 “正确标签”, 我们的 loss 在原本的 cross-entropy 形式上乘以 `vt`, 用 `vt` 来告诉算出来的梯度是不是一个值得信任的梯度. 

如果 `vt` 小, 或者是负的, 就说明这个梯度下降是一个错误的方向, 我们应该向着另一个方向更新参数, 

如果这个 `vt` 是正的, 或很大, `vt` 就会称赞 cross-entropy 出来的梯度, 并朝着这个方向梯度下降。

[![Policy Gradients 思维决策 (Tensorflow)](https://morvanzhou.github.io/static/results/reinforcement-learning/5-2-4.png)](https://morvanzhou.github.io/static/results/reinforcement-learning/5-2-4.png)






#### 3. 关于记忆存储

DQN 的精髓部分之一: 

记录下所有经历过的步, 这些步可以进行反复的学习, 所以是一种 **off-policy** 方法, 你甚至可以自己玩, 然后记录下自己玩的经历, 让这个 DQN 学习你是如何通关的.



存在一个提前限定大小的记忆空间，用于之后随机选取来更新神经网络的参数。

其中存储 [s, a, r, s_]。

s，s_ 为状态，r 为reward，a 为action。

```python
class DeepQNetwork:
    def __init__(self):
        ...
    def store_transition(self, s, a, r, s_):
        if not hasattr(self, 'memory_counter'):
            self.memory_counter = 0

        # 记录一条 [s, a, r, s_] 记录
        transition = np.hstack((s, [a, r], s_))

        # 总 memory 大小是固定的, 如果超出总大小, 旧 memory 就被新 memory 替换
        index = self.memory_counter % self.memory_size
        self.memory[index, :] = transition # 替换过程

        self.memory_counter += 1
```



#### 4. 模型训练/学习过程

最重要的一步来了, 就是在 `DeepQNetwork` 中, 是如何学习, 更新参数的。
这里涉及了 `target_net` 和 `eval_net` 的交互使用。

假如在这个 batch 中, 我们有2个提取的记忆, 根据每个记忆可以生产3个 action 的值:

 将 q_eval 全部赋值给 q_target, 这时 q_target-q_eval 全为 0,
 再根据 batch_memory 当中的 action 这个 column 来给 q_target 中的对应的 memory-action 位置来修改赋值.
**q_target= reward + gamma * maxQ(s_),**

 q_target-q_eval 就可以变成我们所需的样子.

具体在下面还有一个举例说明
    
    q_eval =
    [[1, 2, 3],
    [4, 5, 6]]
    
    q_target = q_eval =
    [[1, 2, 3],
     [4, 5, 6]]
    
    然后根据 memory 当中的具体 action 位置来修改 q_target 对应 action 上的值:
    比如在:
        记忆 0 的 q_target 计算值是 -1, 而且我用了 action 0;
        记忆 1 的 q_target 计算值是 -2, 而且我用了 action 2:
    q_target =
    [[-1, 2, 3],
     [4, 5, -2]]
    
    所以 (q_target - q_eval) 就变成了:
    [[(-1)-(1), 0, 0],
     [0, 0, (-2)-(6)]]
    
    最后我们将这个 (q_target - q_eval) 当成误差, 反向传递给神经网络做参数更新。


