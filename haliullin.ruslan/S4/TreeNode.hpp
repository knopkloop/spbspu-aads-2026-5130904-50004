#ifndef TREENODE_HPP
#define TREENODE_HPP

#include <utility>

namespace haliullin
{
  namespace detail
  {
    template< class Key, class Value >
    struct TreeNode
    {
      TreeNode();
      TreeNode(const Key& key, const Value& value, TreeNode* parent = nullptr);

      std::pair< const Key, Value > data_;
      TreeNode* left_;
      TreeNode* right_;
      TreeNode* parent_;

      static TreeNode fakeLeaf_;
      bool isFake() const noexcept;
    };
  }
}

template< class Key, class Value >
haliullin::detail::TreeNode< Key, Value >::TreeNode():
  data_{},
  left_(nullptr),
  right_(nullptr),
  parent_(nullptr)
{
  left_ = right_ = this;
}

template< class Key, class Value >
haliullin::detail::TreeNode< Key, Value >::TreeNode(const Key& key, const Value& value,
haliullin::detail::TreeNode< Key, Value >* parent):
  data_(key, value),
  left_(std::addressof(fakeLeaf_)),
  right_(std::addressof(fakeLeaf_)),
  parent_(parent)
{}

template< class Key, class Value >
haliullin::detail::TreeNode< Key, Value > haliullin::detail::TreeNode< Key, Value >::fakeLeaf_;

template< class Key, class Value >
bool haliullin::detail::TreeNode< Key, Value >::isFake() const noexcept
{
  return this == std::addressof(fakeLeaf_);
}

#endif
