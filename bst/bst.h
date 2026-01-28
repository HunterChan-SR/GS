#ifndef BST_H
#define BST_H

#include <cstddef>
#include <vector>
#include "logger/logger.h"
#include "data_tools/data_strtct/data_struct.h"
#include <memory>
#include <queue>

/**
 * BST 节点结构体
 * T 必须支持 < 运算符
 */
template <typename T>
struct BSTNode
{
    T data;
    std::unique_ptr<BSTNode> left;
    std::unique_ptr<BSTNode> right;
};

/**
 * 通用二叉搜索树 (BST) 实现
 * T 必须支持 < 运算符
 */

template <typename T>
class BST
{
private:
    /**
     * BST 根节点
     */
    std::unique_ptr<BSTNode<T>> root;

    /**
     * 从有序数组递归构建平衡 BST 节点
     * @param items 有序数组
     * @param start 起始索引
     * @param end 结束索引
     * @return 构建好的 BST 节点
     */
    static std::unique_ptr<BSTNode<T>> build_node_from_sorted(
        const std::vector<T> &items, int64 start, int64 end)
    {
        if (start > end)
            return nullptr;
        int64 mid = (start + end) / 2;

        auto node = std::make_unique<BSTNode<T>>();
        node->data = items[mid];
        node->left = build_node_from_sorted(items, start, mid - 1);
        node->right = build_node_from_sorted(items, mid + 1, end);
        return node;
    }

public:
    /**
     * 默认构造函数
     */
    BST() = default;

    /**
     * 从有序数组构建平衡 BST
     * @param items 有序数组
     * @param start 起始索引
     * @param end 结束索引
     * @return 构建好的 BST
     */
    static BST<T> build_tree_from_sorted(const std::vector<T> &items, int64 start, int64 end)
    {

        BST<T> tree;
        tree.root = build_node_from_sorted(items, start, end);
        return tree;
    }

    /**
     * 从无序数组构建平衡 BST
     * @param items 无序数组
     * @return 构建好的 BST
     */
    static BST<T> build_tree(std::vector<T> &items)
    {
        std::sort(items.begin(), items.end());
        return build_tree_from_sorted(items, 0, items.size() - 1);
    }

    /**
     * 打印 BST 结构（按层次遍历 BFS） 
     */
    void log_tree_bfs() const
    {
        Logger::Info("==========================================================================================");
        Logger::Info("BST Structure (BFS):");
        if (!root)
        {
            Logger::Info("(empty)");
            return;
        }
        std::queue<const BSTNode<T> *> que[2];
        int level = 0;
        que[level & 1].push(root.get());
        while (!que[0].empty() || !que[1].empty())
        {
            std::string line = "Level " + std::to_string(level) + ":";
            while (!que[level & 1].empty())
            {
                const BSTNode<T> *node = que[level & 1].front();
                que[level & 1].pop();
                line += " " + to_string_any(node->data);
                if (node->left)
                    que[(level + 1) & 1].push(node->left.get());
                if (node->right)
                    que[(level + 1) & 1].push(node->right.get());
            }
            Logger::Info(line);
            level++;
        }
        Logger::Info("==========================================================================================");
    }

    /**
     * 打印 BST 结构（按深度优先遍历 DFS）
     */
    void log_tree_dfs() const
    {
        Logger::Info("==========================================================================================");
        Logger::Info("BST Structure (DFS):");
        if (!root)
        {
            Logger::Info("(empty)");
            return;
        }
        log_node_dfs(root.get(), 0, "(Root)");
        Logger::Info("==========================================================================================");
    }

private:
    /**
     * 递归打印 BST 节点（DFS）
     * @param node 当前节点
     * @param prefix_cnt 前缀层数
     * @param title 节点标题
     */
    void log_node_dfs(const BSTNode<T> *node, int prefix_cnt, const std::string &title) const
    {
        if (!node)
            return;
        std::string line;
        for (int i = 0; i < prefix_cnt; ++i)
            line += "|    ";
        line += "|--- " + title + " ";
        Logger::Info(line + to_string_any(node->data));
        if (node->left)
            log_node_dfs(node->left.get(), prefix_cnt + 1, "(Left)");
        if (node->right)
            log_node_dfs(node->right.get(), prefix_cnt + 1, "(Right)");
    }
};

/**
 * 从 RocksDB 数据库中指定 bucket 构建 BST
 * @param db_path RocksDB 数据库路径
 * @param bucket_id 桶 ID
 * @return 构建好的 BST
 */
BST<UserData> build_bst_from_users_db(const std::string db_path, uint64 bucket_id);


#endif // BST_H