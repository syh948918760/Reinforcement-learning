### Deep Q Network

#### 1. 主要思想

主要思想基于Q_Learning。

选择动作仍然基于各个action的Q值。

一个训练的Evaluation-Net， 一个Target-Net， 利用loss，修改Evaluation的神经网络参数。

```python
class DeepQNetwork:
    # 上次的内容
    def _build_net(self):

    # 这次的内容:
    # 初始值
    def __init__(self):

    # 存储记忆
    def store_transition(self, s, a, r, s_):

    # 选行为
    def choose_action(self, observation):

    # 学习
    def learn(self):

    # 看看学习效果 (可选)
    def plot_cost(self):
```



#### 2. Target

Target来源于Evaluation。

比如1000steps为一个周期， 将Evaluation的参数全部赋给Target，在之后的1000次训练内，可以看作Target是fix的，从而完成一个比较好的训练稳定性。

同时，避免的了连续状态内易产生相关性的潜在隐患。



####3. 关于记忆存储

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


