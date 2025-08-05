fs:
- superblock (fs info):
    - fs address
    - file count
- entry table (list of file entries):
    - entry:
        - filename
        - tag (alternative to dirs ~~inspired~~ basically stolen idea from osakaOS)
        - data_start
        - data_length
- data area (dumping ground of asorted file data only navigatable via entries)

fs info:
- fixed size data blocks: each file has the exact same amount of space regardless of content
    - pros:
        - fast
        - easy
    - cons:
        - wasteful of space
