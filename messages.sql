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

 Date: 20/08/2025 11:46:57
*/

SET NAMES utf8mb4;
SET FOREIGN_KEY_CHECKS = 0;

-- ----------------------------
-- Table structure for messages
-- ----------------------------
DROP TABLE IF EXISTS `messages`;
CREATE TABLE `messages`  (
  `id` int NOT NULL AUTO_INCREMENT,
  `sender` int NOT NULL,
  `target` int NOT NULL,
  `content` longtext CHARACTER SET utf8mb4 COLLATE utf8mb4_0900_ai_ci NULL,
  `isImage` tinyint(1) NULL DEFAULT 0,
  `timestamp` datetime NULL DEFAULT CURRENT_TIMESTAMP,
  PRIMARY KEY (`id`) USING BTREE
) ENGINE = InnoDB AUTO_INCREMENT = 26 CHARACTER SET = utf8mb4 COLLATE = utf8mb4_0900_ai_ci ROW_FORMAT = Dynamic;

-- ----------------------------
-- Records of messages
-- ----------------------------
INSERT INTO `messages` VALUES (1, 123456789, 0, '12346465646', 0, '2025-08-15 14:51:38');
INSERT INTO `messages` VALUES (2, 123456789, 0, '12', 0, '2025-08-15 14:51:43');
INSERT INTO `messages` VALUES (3, 123456789, 0, '11', 0, '2025-08-15 14:55:04');
INSERT INTO `messages` VALUES (4, 123456789, 123, '111111', 0, '2025-08-15 15:05:37');
INSERT INTO `messages` VALUES (5, 123456987, 123456789, '刘源明大霸', 0, '2025-08-15 15:06:23');
INSERT INTO `messages` VALUES (6, 123456789, 0, '111', 0, '2025-08-15 15:10:07');
INSERT INTO `messages` VALUES (7, 123, 123456789, '哈喽', 0, '2025-08-15 15:10:32');
INSERT INTO `messages` VALUES (8, 123456789, 123, '11', 0, '2025-08-15 15:10:53');
INSERT INTO `messages` VALUES (9, 123456789, 0, '11', 0, '2025-08-15 15:10:56');
INSERT INTO `messages` VALUES (10, 123, 123456789, '123', 0, '2025-08-15 15:11:00');
INSERT INTO `messages` VALUES (11, 123, 0, '123464', 0, '2025-08-15 15:11:04');
INSERT INTO `messages` VALUES (12, 123456789, 123, '1223', 0, '2025-08-15 15:12:25');
INSERT INTO `messages` VALUES (13, 123, 123456789, '哈哈哈哈哈哈哈哈哈哈哈', 0, '2025-08-15 15:14:59');
INSERT INTO `messages` VALUES (14, 123456789, 123, '1231545646465', 0, '2025-08-15 15:27:57');
INSERT INTO `messages` VALUES (15, 123456789, 0, '法修散打', 0, '2025-08-15 17:15:04');
INSERT INTO `messages` VALUES (16, 123456789, 0, '嗨嗨嗨嗨嗨嗨', 0, '2025-08-18 11:32:39');
INSERT INTO `messages` VALUES (19, 123456789, 0, '465464', 0, '2025-08-18 17:37:19');
INSERT INTO `messages` VALUES (20, 123456789, 0, '12315646', 0, '2025-08-18 17:38:24');

SET FOREIGN_KEY_CHECKS = 1;
