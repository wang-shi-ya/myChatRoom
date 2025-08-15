/*
 Navicat Premium Data Transfer

 Source Server         : cppchat
 Source Server Type    : MySQL
 Source Server Version : 90000 (9.0.0)
 Source Host           : localhost:3306
 Source Schema         : chatroom

 Target Server Type    : MySQL
 Target Server Version : 90000 (9.0.0)
 File Encoding         : 65001

 Date: 15/08/2025 14:10:46
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for user
-- ----------------------------
DROP TABLE IF EXISTS `user`;
CREATE TABLE `user`  (
  `account` int NOT NULL,
  `username` varchar(20) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NOT NULL,
  `password` varchar(20) CHARACTER SET utf8mb3 COLLATE utf8mb3_general_ci NOT NULL,
  `createTime` datetime NOT NULL,
  PRIMARY KEY (`account`) USING BTREE
) ENGINE = InnoDB CHARACTER SET = utf8mb3 COLLATE = utf8mb3_general_ci ROW_FORMAT = DYNAMIC;

-- ----------------------------
-- Records of user
-- ----------------------------
INSERT INTO `user` VALUES (123456789, '用户0', '123456789', '2025-08-14 16:19:59');
INSERT INTO `user` VALUES (123456987, '刘源明大霸', '123456789', '2025-08-15 10:02:56');

SET FOREIGN_KEY_CHECKS = 1;
