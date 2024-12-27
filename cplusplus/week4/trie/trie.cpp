#include "trie.h"
#include <string_view>
using namespace std;

template <class T>
auto Trie::Get(std::string_view key) const -> const T * {
  auto node = root_;
  for(char ch : key){
    if(node == nullptr || node->children_.find(ch) == node->children_.end()){
      return nullptr;
    }
    node = node->children_.at(ch);
  }

  const auto *value_node = dynamic_cast<const TrieNodeWithValue<T> *>(node.get());
  if(value_node != nullptr){
    return value_node->value_.get();
  }
  return nullptr;
  // You should walk through the trie to find the node corresponding to the key. If the node doesn't exist, return
  // nullptr. After you find the node, you should use `dynamic_cast` to cast it to `const TrieNodeWithValue<T> *`. If
  // dynamic_cast returns `nullptr`, it means the type of the value is mismatched, and you should return nullptr.
  // Otherwise, return the value.
  throw "Trie::Get is not implemented.";
}
template <class T>
void cycle_put(shared_ptr<TrieNode> &new_root, string_view key, T value){
  bool flag = false;
  for(auto &pair : new_root->children_){
    if(key[0] == pair.first){
      flag = true;
      if(key.size() > 1){
        shared_ptr<TrieNode> ptr = pair.second->Clone();
        cycle_put<T>(ptr, key.substr(1), move(value));
        pair.second = shared_ptr<TrieNode>(ptr);
      }else{
        shared_ptr<T> val_p = make_shared<T>(move(value));
        TrieNodeWithValue new_node(pair.second->children_, val_p);
        pair.second = make_shared<TrieNodeWithValue<T>>(new_node);
      }
      return;
    }
  }
  if(flag == false){
    char c = key.at(0);
    if(key.size() == 1){
      shared_ptr<T> val_p = make_shared<T>(move(value));
      new_root->children_.insert({c, make_shared<TrieNodeWithValue<T>>(val_p)});
    }else{
      auto ptr = make_shared<TrieNode>();
      cycle_put(ptr, key.substr(1), move(value));
      new_root->children_.insert({c, move(ptr)});
    }

  }
}
template <class T>
auto Trie::Put(std::string_view key, T value) const -> Trie {
  if(key.empty()){
    std::shared_ptr<T> val_p = std::make_shared<T>(std::move(value));
    std::unique_ptr<TrieNodeWithValue<T>> new_root = nullptr;

    if(root_->children_.empty()){
      new_root = std::make_unique<TrieNodeWithValue<T>>(std::move(val_p));
    }else{
      new_root = std::make_unique<TrieNodeWithValue<T>>(root_->children_, std::move(val_p));
    }
    return Trie(std::move(new_root));
  }else{
    shared_ptr<TrieNode> new_root = nullptr;
    if(root_ == nullptr){
      new_root = make_unique<TrieNode>();
    }else{
      new_root = root_->Clone();
    }

    cycle_put(new_root, key, move(value));
    return Trie(move(new_root));
  }
  // Note that `T` might be a non-copyable type. Always use `std::move` when creating `shared_ptr` on that value.
  // You should walk through the trie and create new nodes if necessary. If the node corresponding to the key already
  // exists, you should create a new `TrieNodeWithValue`.
  
}

bool cycle_remove(string_view key, shared_ptr<TrieNode> &new_root){
  for(auto &item : new_root->children_){
    if(key[0] != item.first){
      continue;
    }
    if(key.size() == 1){
      if(!item.second->is_value_node_){
        return false;
      }
      if(item.second->children_.empty()){
        new_root->children_.erase(item.first);
      }else{
        item.second = make_shared<TrieNode>(item.second->children_);
      }
      return true;
    }else{
      shared_ptr<TrieNode> ptr = item.second->Clone();
      bool flag = cycle_remove(key.substr(1, key.size() - 1), ptr);

      if(!flag){
        return false;
      }
      if(ptr->children_.empty() && !ptr->is_value_node_){
        new_root->children_.erase(item.first);
      }else{
        item.second = shared_ptr<TrieNode>(ptr); 
      }
      return true;
    }
    
  }
  return false;
}

auto Trie::Remove(std::string_view key) const -> Trie {
  if(this->root_ == nullptr){
    return *this;
  }
  if(key.empty()){
    if(root_->is_value_node_){
      if(!root_->children_.empty()){
        shared_ptr<TrieNode> new_node = make_shared<TrieNode>(root_->children_);
        return Trie(new_node);
      }else{
        return Trie();
      }

    }else{
      return *this;
    }
  }else{
    shared_ptr<TrieNode> new_root = root_->Clone();
    bool flag = cycle_remove(key, new_root);
    if(!flag){
      return *this;
    }
    if(new_root->children_.empty() && !new_root->is_value_node_){
      new_root = nullptr;
    }
    return Trie(move(new_root));
  }
  // You should walk through the trie and remove nodes if necessary. If the node doesn't contain a value any more,
  // you should convert it to `TrieNode`. If a node doesn't have children any more, you should remove it.
  throw "Trie::Remove is not implemented.";
}

// Below are explicit instantiation of template functions.
//
// Generally people would write the implementation of template classes and functions in the header file. However, we
// separate the implementation into a .cpp file to make things clearer. In order to make the compiler know the
// implementation of the template functions, we need to explicitly instantiate them here, so that they can be picked up
// by the linker.

template auto Trie::Put(std::string_view key, uint32_t value) const -> Trie;
template auto Trie::Get(std::string_view key) const -> const uint32_t *;

template auto Trie::Put(std::string_view key, uint64_t value) const -> Trie;
template auto Trie::Get(std::string_view key) const -> const uint64_t *;

template auto Trie::Put(std::string_view key, std::string value) const -> Trie;
template auto Trie::Get(std::string_view key) const -> const std::string *;

// If your solution cannot compile for non-copy tests, you can remove the below lines to get partial score.

using Integer = std::unique_ptr<uint32_t>;

template auto Trie::Put(std::string_view key, Integer value) const -> Trie;
template auto Trie::Get(std::string_view key) const -> const Integer *;

template auto Trie::Put(std::string_view key, MoveBlocked value) const -> Trie;
template auto Trie::Get(std::string_view key) const -> const MoveBlocked *;
