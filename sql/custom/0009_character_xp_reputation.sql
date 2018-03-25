-- ================================================
-- Table structure for table `characters_limited`
-- ================================================

ALTER TABLE `characters_limited`
  ADD COLUMN `xp_rate` float NOT NULL DEFAULT '0' AFTER `guid`,
  ADD COLUMN `xp_time` int(11) unsigned NOT NULL DEFAULT '0' AFTER `xp_rate`,
  ADD COLUMN `reputation_rate` float NOT NULL DEFAULT '0' AFTER `xp_time`,
  ADD COLUMN `reputation_time` int(11) unsigned NOT NULL DEFAULT '0' AFTER `reputation_rate`;