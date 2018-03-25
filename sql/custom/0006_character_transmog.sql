--
-- Table structure for table `character_transmog`
--
CREATE TABLE `character_transmog` (
  `guid` int(20) unsigned NOT NULL default '0',
  `slot` int(8) unsigned NOT NULL default '0',
  `item_guid` int(20) unsigned NOT NULL default '0',
  `flags` int(20) unsigned NOT NULL default '0',
  KEY `idx_guid` (`guid`),
  PRIMARY KEY (`guid`,`slot`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;